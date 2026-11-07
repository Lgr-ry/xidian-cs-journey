/**
 ******************************************************************************
 * @file    main.c
 * @brief   MEIC 智能寻迹小车 · 基础任务版（STM32F103C8T6，标准外设库，无需 CubeMX）
 *
 * ======================== RUN_MODE 一览 ========================
 *   10 = 【基础任务全流程】任务一 → 任务二 → 任务三（任务状态机，运行时可切换）
 *    0 = 调试·双轮等速走直线
 *    1 = 调试·纯巡线（不转弯）
 *    2 = 调试·巡线 + 单个直角转弯
 *    3 = 灰度 8 路标定（只读，不驱动电机）
 *    4 = 电机自检（纯前馈，两轮前进/后退/停循环）
 *    6 = 自动配平（探一次，结果放 g_trim 供 Watch 查看）
 * ==============================================================
 *
 * ★ 重要约束（学长口径）：**验收中途不能重新烧录程序**。
 *   所以任务切换必须能"运行中"完成 —— 使用全局 g_task：
 *     在 Keil 调试的 Watch 窗口里把 g_task 的值改成 0/1/2（见 g_dbg 说明），
 *     或者直接改 #define TASK_START 后重烧。上电从 TASK_START 开始，跑完按 LOOP_ALL 决定循环还是停。
 *
 * ★ 两轮同步：用自动配平 g_trim（同样的 PWM 下两轮脉冲比 ≈ 右轮当量/左轮当量）。
 *   上电按住车 0.8 秒会让它自己配平（AUTO_TRIM=1），或先跑 RUN_MODE=6 读出 g_trim 填进 RIGHT_TRIM。
 ******************************************************************************
 */
#include "stm32f10x.h"
#include <stdio.h>

#include "bsp_time.h"
#include "motor.h"
#include "encoder.h"
#include "pid.h"
#include "track.h"
#include "uart.h"

/* ==========================================================================
 * 1) 运行模式
 * ========================================================================== */
#define RUN_MODE            10          /* 10=基础任务全流程；其它见文件头 */

/* ==========================================================================
 * 2) 速度与两轮同步
 * ========================================================================== */
#define SPEED_CMPS          18.0f       /* 巡线速度 cm/s（只影响快慢，不影响走不走得直） */
#define PULSE_PER_CM        65.0f       /* 脉冲/厘米（定距停车与转弯角度用，现场实测） */
#define SPEED_PULSES        (SPEED_CMPS * PULSE_PER_CM / 100.0f)   /* ≈ 11.7 脉冲/10ms */

#define WHEEL_TRACK_CM      15.0f       /* 左右轮中心距 cm */
#define TURN90_PULSE        (int32_t)((WHEEL_TRACK_CM / 2.0f) * 1.5707963f * PULSE_PER_CM)
/* 原地转 90°：单侧轮弧长 =(轮距/2)×(π/2) 再乘脉冲当量 */
#define BASE_PWM            3000.0f     /* 前馈 PWM（0~7199） */

#define AUTO_TRIM           1           /* 1=上电自动配平（车会空转 0.8 秒！先按住车） */
#define RIGHT_TRIM          1.00f       /* 手动补偿；用 g_trim 的值填这里 */
#define PROBE_PWM           2600
#define PROBE_MS            800
#define TRIM_MIN            0.5f
#define TRIM_MAX            2.0f

/* ==========================================================================
 * 3) 控制周期与 PID
 *    ⚠️ CTRL_PERIOD_MS 不要乱改：PID 增益是按 10ms 整定的
 * ========================================================================== */
#define CTRL_PERIOD_MS      10
#define SPEED_KP            10.0f
#define SPEED_KI            1.2f        /* 抖动/蛇形就降到 0.6 */
#define SPEED_KD            0.0f
#define DIR_KP              3.5f
#define DIR_KD              12.0f
#define DIR_OUT_LIMIT       10.0f

/* ==========================================================================
 * 4) 基础任务参数（★ 带【现场】标记的必须到场地实测后改）
 * ========================================================================== */
#define TASK_START          0           /* 上电从哪个任务开始：0=任务一 1=任务二 2=任务三 */
#define TEST_RUN0_STOP_CM   0.0f        /* ★ RUN_MODE=0 调试直行的定距停车：0=一直走不停车 */
#define LOOP_ALL            0           /* 1=跑完最后一项回到第一项继续（一直转）；0=跑完停 */
#define TASK_TIMEOUT_MS     45000UL     /* 单个任务超时兜底（防止卡死永远不结束） */

/* ---- 任务一：巡线一周（A→B ＋ 绕场一周）---- */
#define LAP_CORNERS         4           /* 一圈要过几个直角 */
#define CORNER_BLACK_MIN    4           /* 【现场】直角处至少几路压黑才算"到弯"（先试 4） */
#define CORNER_DEBOUNCE     3           /* 连续几个控制周期满足才算数（防抖） */
#define LEAVE_MS            250         /* 转完弯先直行这么久，离开横线再回巡线 */
#define LAP_END_CM          10.0f       /* 【现场】最后一弯过后再走多远认为"回到 A" */

/* ---- 任务二：倒车入库 ＋ 侧方停车（动作序列，数值全部【现场】标定）---- */
#define PARK_SPD            11.0f       /* 泊车速度（脉冲/10ms） */
#define PARK_ALIGN_CM       12.0f       /* 【现场】① 前进对准：走多少 cm */
#define PARK_PAUSE_MS       400         /* 停稳时间 */
#define PARK_BACK_CM        22.0f       /* 【现场】② 倒车入库：倒多少 cm */
#define PARK_TURN_DEG       60.0f       /* 【现场】② 入库转角（度） */
#define PARK_CORRECT_CM     8.0f        /* 【现场】③ 摆正再退多少 cm */
#define PARK_PARALLEL_CM    25.0f       /* 【现场】④ 侧方停车：先向前开过车位多少 cm */
#define PARK_ARC_CM         18.0f       /* 【现场】⑤ 侧方倒车弧长 cm */

/* ---- 任务三：罗马数字识别定点停车（摄像头经串口给 A/B/C/D）---- */
#define STOP_POINT_NUM      4           /* 可停靠的点数：A B C D */
#define STOP_OFFSET_CM      6.0f        /* 【现场】到点后再走多少 cm 停车（不压线） */
#define CAM_WAIT_MS         30000UL     /* 等摄像头数据的超时；超时就停 */
#define CAM_DEFAULT_POINT   1           /* 收不到数据时默认去哪（1=B） */

/* ==========================================================================
 * 5) 全局量
 * ========================================================================== */
static PID_t s_pidLeft;
static PID_t s_pidRight;

/* 给 Keil Watch 看的全局量（没有串口就靠它） */
int16_t g_encL = 0, g_encR = 0;
float   g_tgtL = 0, g_tgtR = 0;
int16_t g_pwmL = 0, g_pwmR = 0;
int32_t g_sumL = 0, g_sumR = 0;
float   g_trim = 1.0f;
int8_t  g_signL = 0, g_signR = 0;

volatile uint8_t g_task = TASK_START;   /* ★ 运行中可改：Watch 里改这个值就换任务 */
volatile uint8_t g_stopAll = 0;         /* ★ 置 1 = 全部停车（Watch 里可改回 0 恢复） */
int32_t g_dbg[8];                       /* ★ 调试一览：Watch 直接看这个数组 */

/* 巡线子状态机 */
enum { ST_TRACK = 0, ST_TURNING = 1, ST_LEAVE = 2 };

/* 泊车动作类型 */
#define ST_STRAIGHT 0       /* 直行/直退：按距离(脉冲)停 */
#define ST_ARC      1       /* 弧线（两轮速度不同）：按距离(脉冲)停 */
#define ST_TURN     2       /* 原地转：按脉冲(角度)停 */
#define ST_WAIT     3       /* 停住：按时间停 */

typedef struct { uint8_t type; int16_t vL; int16_t vR; float amount; } Step_t;

/* ==========================================================================
 * 6) 基础工具
 * ========================================================================== */

/* 串口收一个字节：返回 −1 表示暂时没有数据（uart.c 已开 RX，直接用） */
static int UART_TryGetChar(void)
{
    if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET)
    {
        return (int)(USART_ReceiveData(USART1) & 0xFF);
    }
    return -1;
}

/* 读 8 路灰度，返回"压黑的路数"（用于判断直角/路口） */
static uint8_t Track_BlackCount(void)
{
    uint8_t i, n = 0;
    for (i = 0; i < 8; i++)
    {
        if (Track_ReadADC(i) < TRACK_THRESHOLD) n++;
    }
    return n;
}

/**
 * @brief 自动配平：两轮同 PWM 跑 PROBE_MS，测脉冲比 ≈ 右轮当量/左轮当量。
 */
static void AutoTrim(void)
{
    int32_t nL = 0, nR = 0, netL = 0, netR = 0;
    uint32_t t0, last;
    int16_t  a, b;

    Motor_Set(PROBE_PWM, PROBE_PWM);
    last = BSP_Millis();
    t0   = last;
    while (BSP_Millis() - t0 < PROBE_MS)
    {
        BSP_Time_Tick();
        if (BSP_Millis() - last >= CTRL_PERIOD_MS)
        {
            last += CTRL_PERIOD_MS;
            Encoder_Get(&a, &b);
            nL   += (a >= 0 ? a : -a);
            nR   += (b >= 0 ? b : -b);
            netL += a;
            netR += b;
        }
    }
    Motor_Stop();
    BSP_DelayMs(200);

    g_signL = (netL >= 0) ? 1 : -1;
    g_signR = (netR >= 0) ? 1 : -1;

    if (nL >= 50 && nR >= 50)
    {
        g_trim = (float)nR / (float)nL;
        if (g_trim < TRIM_MIN) g_trim = TRIM_MIN;
        if (g_trim > TRIM_MAX) g_trim = TRIM_MAX;
    }
    printf("AUTO TRIM: nL=%ld nR=%ld trim=%.3f signL=%d signR=%d\r\n",
           (long)nL, (long)nR, g_trim, (int)g_signL, (int)g_signR);
}

/* 单轮速度闭环：前馈 + PID（不要在这里 return，否则闭环失效） */
static int16_t Speed_Loop(float target, int16_t encoder, PID_t *pid)
{
    float feedForward = 0.0f;
    float out;

    if (target > 0.01f)        feedForward =  BASE_PWM;
    else if (target < -0.01f)  feedForward = -BASE_PWM;

    out = feedForward + PID_Calc(pid, (float)encoder);

    if (out >  MOTOR_PERIOD) out =  MOTOR_PERIOD;
    if (out < -MOTOR_PERIOD) out = -MOTOR_PERIOD;
    return (int16_t)out;
}

/* ==========================================================================
 * 7) 巡线核心（任务一 / 任务三共用）
 *    返回 1 = 刚刚完成一次直角转弯；同时更新 targetL/targetR
 * ========================================================================== */
static uint8_t s_sub = ST_TRACK;
static uint32_t s_leaveStart = 0;
static int32_t  s_turnAcc = 0;
static uint8_t  s_blackRun = 0;
static float    s_lastErr = 0.0f;
static volatile uint8_t s_newTask = 1;   /* 任务切换后置 1，任务自己复位内部状态 */
static uint8_t s_armed = 0;              /* 见过"正常单线"(1~3 路压黑)后才允许判直角 */

static uint8_t Line_Follow(float *tL, float *tR, int16_t eL, int16_t eR,
                           float baseL, float baseR)
{
    float err  = (float)Track_Error();
    float dErr = err - s_lastErr;
    float turn = DIR_KP * err + DIR_KD * dErr;
    uint8_t black = Track_BlackCount();
    uint8_t justTurned = 0;

    s_lastErr = err;
    if (turn >  DIR_OUT_LIMIT) turn =  DIR_OUT_LIMIT;
    if (turn < -DIR_OUT_LIMIT) turn = -DIR_OUT_LIMIT;

    /* 先武装：见过一次"正常单线"才允许判直角——避免起步时压在线上就误判 */
    if (black >= 1 && black < CORNER_BLACK_MIN) s_armed = 1;

    /* 连续压黑计数（去抖） */
    if (s_armed && black >= CORNER_BLACK_MIN) { if (s_blackRun < 255) s_blackRun++; }
    else                                        s_blackRun = 0;

    switch (s_sub)
    {
    case ST_TRACK:
        *tL = baseL + turn;
        *tR = baseR - turn;
        if (s_blackRun >= CORNER_DEBOUNCE)          /* 到弯了 */
        {
            s_sub = ST_TURNING;
            s_turnAcc = 0;
            PID_Reset(&s_pidLeft);
            PID_Reset(&s_pidRight);
        }
        break;

    case ST_TURNING:
        *tL =  (float)SPEED_PULSES;                 /* 原地右转：左轮前进、右轮后退 */
        *tR = -(float)SPEED_PULSES;
        s_turnAcc += (int32_t)(((eL >= 0 ? eL : -eL) + (eR >= 0 ? eR : -eR)) / 2);
        if (s_turnAcc >= TURN90_PULSE)
        {
            s_sub = ST_LEAVE;
            s_leaveStart = BSP_Millis();
            s_lastErr = 0.0f;
            PID_Reset(&s_pidLeft);
            PID_Reset(&s_pidRight);
            justTurned = 1;                         /* 转完一个直角 */
            s_blackRun = 0;
        }
        break;

    default:  /* ST_LEAVE：先直行一小段离开横线 */
        *tL = baseL;
        *tR = baseR;
        if ((BSP_Millis() - s_leaveStart > LEAVE_MS)) s_sub = ST_TRACK;
        break;
    }

    if (*tL < 0.0f) *tL = 0.0f;
    if (*tR < 0.0f) *tR = 0.0f;
    return justTurned;
}

/* ==========================================================================
 * 8) 任务一：巡线一周（A→B ＋ 绕场一周）
 * ========================================================================== */
static uint8_t Task_Line(float *tL, float *tR, int16_t eL, int16_t eR,
                         float baseL, float baseR)
{
    static uint8_t corners = 0;

    if (s_newTask) { s_newTask = 0; corners = 0; s_sub = ST_TRACK; g_dbg[2] = 0; }

    if (Line_Follow(tL, tR, eL, eR, baseL, baseR))
    {
        corners++;
        g_dbg[2] = corners;
    }

    if (corners >= LAP_CORNERS)                     /* 转完最后一弯 = 回到 A */
    {
        *tL = 0.0f;  *tR = 0.0f;                    /* 任务一结束：停车 */
        return 1;
    }
    return 0;
}

/* ==========================================================================
 * 9) 任务二：倒车入库 ＋ 侧方停车（动作序列，数值现场标定）
 * ========================================================================== */
static const Step_t s_parkSeq[] = {
    /* 类型        左轮            右轮            判据（ST_WAIT 时单位 ms，其它为脉冲） */
    { ST_STRAIGHT,  (int16_t)11,   (int16_t)11,   PARK_ALIGN_CM  * PULSE_PER_CM }, /* ① 前进对准车位 */
    { ST_WAIT,      0,             0,              PARK_PAUSE_MS                  }, /* ② 停稳 */
    { ST_ARC,       (int16_t)-9,   (int16_t)-5,    PARK_BACK_CM   * PULSE_PER_CM }, /* ③ 倒车入库（车尾右摆） */
    { ST_WAIT,      0,             0,              PARK_PAUSE_MS                  }, /* ④ 停稳 */
    { ST_ARC,       (int16_t)8,    (int16_t)4,     PARK_CORRECT_CM * PULSE_PER_CM}, /* ⑤ 摆正 */
    { ST_STRAIGHT,  (int16_t)11,   (int16_t)11,    PARK_PARALLEL_CM * PULSE_PER_CM},/* ⑥ 侧方：开过车位 */
    { ST_WAIT,      0,             0,              PARK_PAUSE_MS                  }, /* ⑦ 停稳 */
    { ST_ARC,       (int16_t)-10,  (int16_t)-6,    PARK_ARC_CM    * PULSE_PER_CM }, /* ⑧ 侧方倒车入位 */
    { ST_WAIT,      0,             0,              PARK_PAUSE_MS                  }, /* ⑨ 停稳（全程结束） */
};
#define PARK_STEPS  (sizeof(s_parkSeq) / sizeof(s_parkSeq[0]))

static uint8_t Task_Park(float *tL, float *tR, int16_t eL, int16_t eR)
{
    static uint8_t  step = 0;
    static int32_t  acc  = 0;
    static uint32_t t0   = 0;
    const Step_t *s;

    if (s_newTask) { s_newTask = 0; step = 0; acc = 0; t0 = BSP_Millis(); g_dbg[3] = 0; }

    if (step >= PARK_STEPS) { *tL = 0.0f; *tR = 0.0f; return 1; }   /* 全部动作做完 */

    s = &s_parkSeq[step];
    g_dbg[3] = step;

    switch (s->type)
    {
    case ST_WAIT:
        *tL = 0.0f;  *tR = 0.0f;
        if (BSP_Millis() - t0 >= (uint32_t)s->amount) { step++; acc = 0; t0 = BSP_Millis(); }
        break;

    case ST_TURN:
        *tL =  (float)s->vL;  *tR = -(float)s->vR;
        acc += (int32_t)(((eL >= 0 ? eL : -eL) + (eR >= 0 ? eR : -eR)) / 2);
        if ((float)acc >= s->amount) { step++; acc = 0; t0 = BSP_Millis(); }
        break;

    default:  /* ST_STRAIGHT / ST_ARC：两轮各给速度，按平均脉冲数停 */
        *tL = (float)s->vL;
        *tR = (float)s->vR;
        acc += (int32_t)(((eL >= 0 ? eL : -eL) + (eR >= 0 ? eR : -eR)) / 2);
        if ((float)acc >= s->amount) { step++; acc = 0; t0 = BSP_Millis(); }
        break;
    }
    return 0;
}

/* ==========================================================================
 * 10) 任务三：罗马数字识别定点停车
 *     摄像头（MaixCAM）通过串口发一个字符 'A'/'B'/'C'/'D'（或 '1'~'4'）表示目标点
 * ========================================================================== */
static uint8_t Task_StopAt(float *tL, float *tR, int16_t eL, int16_t eR,
                           float baseL, float baseR)
{
    static uint8_t  got = 0, target = 0, corners = 0;
    static uint32_t t0 = 0;
    static int32_t  endAcc = 0;
    static uint8_t  stopping = 0;
    int c;

    if (s_newTask) { s_newTask = 0; got = 0; corners = 0; stopping = 0; endAcc = 0; t0 = BSP_Millis(); s_sub = ST_TRACK; }

    /* 1) 先等摄像头给目标点（最多等 CAM_WAIT_MS） */
    if (!got)
    {
        while ((c = UART_TryGetChar()) >= 0)
        {
            if      (c == 'A' || c == '1') { target = 0; got = 1; }
            else if (c == 'B' || c == '2') { target = 1; got = 1; }
            else if (c == 'C' || c == '3') { target = 2; got = 1; }
            else if (c == 'D' || c == '4') { target = 3; got = 1; }
        }
        if (!got && (BSP_Millis() - t0 > CAM_WAIT_MS))
        {
            target = CAM_DEFAULT_POINT;   /* 摄像头没消息：默认去 B 点，别卡死 */
            got = 1;
        }
        *tL = 0.0f;  *tR = 0.0f;          /* 等的时候不动 */
        g_dbg[4] = got;
        if (!got) return 0;
    }

    /* 2) 巡线走到第 target 个点：A 点是起点，过一个直角 = 到下一个点 */
    if (stopping)
    {
        *tL = baseL;  *tR = baseR;
        endAcc += (int32_t)(((eL >= 0 ? eL : -eL) + (eR >= 0 ? eR : -eR)) / 2);
        if ((float)endAcc >= STOP_OFFSET_CM * PULSE_PER_CM)
        {
            *tL = 0.0f;  *tR = 0.0f;      /* 到点停车（不压线） */
            return 1;
        }
        return 0;
    }

    if (Line_Follow(tL, tR, eL, eR, baseL, baseR))   /* 刚过完一个直角 */
    {
        corners++;
        g_dbg[2] = corners;
        if (corners >= target) stopping = 1;          /* 下一个点就是目标点 */
    }

    g_dbg[5] = target;
    return 0;
}

/* ==========================================================================
 * 11) 主程序
 * ========================================================================== */
int main(void)
{
    int16_t encL = 0, encR = 0;
    int16_t pwmL = 0, pwmR = 0;
    float   targetL = 0.0f, targetR = 0.0f;
    float   baseL = 0.0f, baseR = 0.0f;
    float   err = 0.0f, lastErr = 0.0f, dErr = 0.0f;
    float   turn = 0.0f;
    int32_t totalStraight = 0, turnAcc = 0;
    uint8_t state = ST_TRACK;
    uint32_t leaveStart = 0, runStart = 0, lastTick = 0;
    uint8_t  printCnt = 0;
    uint8_t  lastTask = 0xFF;
    uint32_t taskStart = BSP_Millis();

    BSP_Time_Init();
    Motor_Init();
    Encoder_Init();
    Track_Init();
    UART_Init(115200);

    PID_Init(&s_pidLeft,  SPEED_KP, SPEED_KI, SPEED_KD, 3000.0f, 2000.0f);
    PID_Init(&s_pidRight, SPEED_KP, SPEED_KI, SPEED_KD, 3000.0f, 2000.0f);

    BSP_DelayMs(500);

    if (AUTO_TRIM) AutoTrim();         /* 上电自动配平（车会空转 0.8 秒） */
    if (RUN_MODE == 6) AutoTrim();     /* 或手动：RUN_MODE=6 探一次，看 Watch 的 g_trim */

    printf("\r\n==== SmartCar 基础任务版 RUN=%d trim=%.3f ====\r\n",
           (int)RUN_MODE, g_trim);

    runStart = BSP_Millis();
    lastTick = BSP_Millis();
    taskStart = runStart;
    Motor_Stop();

    while (1)
    {
        BSP_Time_Tick();

        if (BSP_Millis() - lastTick >= CTRL_PERIOD_MS)
        {
            lastTick += CTRL_PERIOD_MS;
            Encoder_Get(&encL, &encR);

            /* ---------- 标定/测试模式 ---------- */
            if (RUN_MODE == 3)                       /* 灰度 8 路 */
            {
                Motor_Stop();
                if (++printCnt >= 50)
                {
                    printCnt = 0;
                    printf("CH1=%4u CH2=%4u CH3=%4u CH4=%4u CH5=%4u CH6=%4u CH7=%4u CH8=%4u black=%u\r\n",
                           Track_ReadADC(0), Track_ReadADC(1), Track_ReadADC(2), Track_ReadADC(3),
                           Track_ReadADC(4), Track_ReadADC(5), Track_ReadADC(6), Track_ReadADC(7),
                           (unsigned)Track_BlackCount());
                }
                continue;
            }
            if (RUN_MODE == 4)                       /* 电机自检 */
            {
                uint8_t ph = (uint8_t)((BSP_Millis() / 500UL) % 6UL);
                if (ph == 0 || ph == 1)       Motor_Set( 2000,  2000);
                else if (ph == 3 || ph == 4)  Motor_Set(-2000, -2000);
                else                          Motor_Stop();
                continue;
            }
            if (RUN_MODE == 6)                       /* 只看配平结果 */
            {
                Motor_Stop();
                if (++printCnt >= 50) { printCnt = 0; printf("TRIM=%.3f\r\n", g_trim); }
                continue;
            }

            /* ---------- 基准速度 ---------- */
            baseL = SPEED_PULSES;
            baseR = SPEED_PULSES * g_trim * RIGHT_TRIM;

            /* ---------- RUN_MODE 0/1/2：单功能调试 ---------- */
            if (RUN_MODE == 0 || RUN_MODE == 1 || RUN_MODE == 2)
            {
                targetL = baseL;  targetR = baseR;
                if (RUN_MODE == 0)
                {
                    /* 等速走直线 */
                }
                else
                {
                    err     = (float)Track_Error();
                    dErr    = err - lastErr;
                    lastErr = err;
                    turn    = DIR_KP * err + DIR_KD * dErr;
                    if (turn >  DIR_OUT_LIMIT) turn =  DIR_OUT_LIMIT;
                    if (turn < -DIR_OUT_LIMIT) turn = -DIR_OUT_LIMIT;

                    if (RUN_MODE == 1)
                    {
                        targetL = baseL + turn;
                        targetR = baseR - turn;
                    }
                    else
                    {
                        if (state == ST_TRACK)
                        {
                            targetL = baseL + turn;
                            targetR = baseR - turn;
                            if (Track_IsCross())
                            {
                                state = ST_TURNING; turnAcc = 0;
                                PID_Reset(&s_pidLeft); PID_Reset(&s_pidRight);
                            }
                        }
                        else if (state == ST_TURNING)
                        {
                            targetL =  SPEED_PULSES;
                            targetR = -SPEED_PULSES;
                            turnAcc += (int32_t)(((encL >= 0 ? encL : -encL) +
                                                  (encR >= 0 ? encR : -encR)) / 2);
                            if (turnAcc >= TURN90_PULSE)
                            {
                                state = ST_LEAVE; leaveStart = BSP_Millis();
                                PID_Reset(&s_pidLeft); PID_Reset(&s_pidRight);
                                lastErr = 0.0f;
                            }
                        }
                        else
                        {
                            targetL = baseL;  targetR = baseR;
                            if ((BSP_Millis() - leaveStart > 300UL) && (!Track_IsCross()))
                                state = ST_TRACK;
                        }
                    }
                }

                if (TEST_RUN0_STOP_CM > 0.0f)              /* 0 = 一直走，不自动停 */
                {
                    totalStraight += (encL >= 0 ? encL : -encL);
                    if (totalStraight >= (int32_t)(TEST_RUN0_STOP_CM * PULSE_PER_CM))
                    {
                        Motor_Stop();
                    }
                }
            }
            /* ---------- RUN_MODE 10：基础任务全流程 ---------- */
            else if (RUN_MODE == 10)
            {
                if (g_task != lastTask)                 /* 任务切换：清场 */
                {
                    lastTask  = g_task;
                    taskStart = BSP_Millis();
                    s_newTask = 1;      /* 让任务自己复位内部状态 */
                    s_armed   = 0;      /* 重新武装：换任务后先见到正常单线才判弯 */
                    g_stopAll = 0;      /* 切换任务 = 重新开动 */
                    s_sub = ST_TRACK;  s_blackRun = 0;  s_lastErr = 0.0f;
                    s_turnAcc = 0;     turnAcc = 0;     totalStraight = 0;
                    PID_Reset(&s_pidLeft); PID_Reset(&s_pidRight);
                    printf("ENTER TASK %d\r\n", (int)g_task);
                }

                uint8_t done = 0;
                if      (g_task == 0) done = Task_Line (&targetL, &targetR, encL, encR, baseL, baseR);
                else if (g_task == 1) done = Task_Park(&targetL, &targetR, encL, encR);
                else                  done = Task_StopAt(&targetL, &targetR, encL, encR, baseL, baseR);

                if (BSP_Millis() - taskStart > TASK_TIMEOUT_MS) done = 1;   /* 超时兜底 */

                g_dbg[0] = g_task;
                g_dbg[1] = (int32_t)(g_trim * 1000.0f);

                if (done)
                {
                    if (g_task < 2)        g_task++;                 /* 下一项，中途不停车 */
                    else if (LOOP_ALL)     g_task = 0;               /* 一直转：回到任务一 */
                    else                   g_stopAll = 1;            /* 全部做完：停车保持 */
                }
            }

            /* ---------- 总停车（g_stopAll=1 时保持不动；Watch 里改回 0 即恢复）---------- */
            if (g_stopAll)
            {
                Motor_Stop();
                PID_Reset(&s_pidLeft); PID_Reset(&s_pidRight);
                g_pwmL = 0; g_pwmR = 0; g_tgtL = 0; g_tgtR = 0;
                continue;
            }

            /* ---------- 闭环 + 驱动 ---------- */
            g_encL = encL;    g_encR = encR;
            g_tgtL = targetL; g_tgtR = targetR;
            g_sumL += (encL >= 0 ? encL : -encL);
            g_sumR += (encR >= 0 ? encR : -encR);

            pwmL = Speed_Loop(targetL, encL, &s_pidLeft);
            pwmR = Speed_Loop(targetR, encR, &s_pidRight);
            g_pwmL = pwmL;    g_pwmR = pwmR;
            Motor_Set(pwmL, pwmR);

            /* ---------- 总超时保护 ---------- */
            if (BSP_Millis() - runStart > 180000UL) Motor_Stop();

            /* ---------- 每 50ms 打印一次 ---------- */
            if (++printCnt >= 5)
            {
                printCnt = 0;
                printf("%d,%d,%d,%d\r\n", (int)encL, (int)encR, (int)err, (int)g_task);
            }
        }
    }
}
