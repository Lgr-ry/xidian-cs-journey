/**
 ******************************************************************************
 * @file    motor.c
 * @brief   TB6612 双直流电机驱动实现（标准外设库，无需 CubeMX）
 *          接线：PWMA=PA0, AIN1=PA1, AIN2=PA2, PWMB=PA3
 *                BIN1=PB1, BIN2=PB8, STBY=3V3
 ******************************************************************************
 */
#include "motor.h"

/* 把数值限制在 [-MOTOR_PERIOD, +MOTOR_PERIOD]，防止越界 */
static int16_t Motor_Limit(int16_t v)
{
    if (v >  MOTOR_PERIOD) v =  MOTOR_PERIOD;
    if (v < -MOTOR_PERIOD) v = -MOTOR_PERIOD;
    return v;
}

void Motor_Init(void)
{
    GPIO_InitTypeDef        gpio;
    TIM_TimeBaseInitTypeDef timBase;
    TIM_OCInitTypeDef       timOC;

    /* 开启 GPIOA、GPIOB 与 TIM2 时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,  ENABLE);

    /* 1) 左电机方向：PA1(AIN1)、PA2(AIN2) 推挽输出 */
    gpio.GPIO_Pin   = GPIO_Pin_1 | GPIO_Pin_2;
    gpio.GPIO_Mode  = GPIO_Mode_Out_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio);

    /* 2) 右电机方向：PB1(BIN1)、PB8(BIN2) 推挽输出 */
    gpio.GPIO_Pin   = GPIO_Pin_1 | GPIO_Pin_8;
    GPIO_Init(GPIOB, &gpio);

    /* 3) PWM 引脚 PA0/PA3：复用推挽输出 */
    gpio.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_3;
    gpio.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &gpio);

    /*
     * 4) TIM2 时基：PSC=0，ARR=7199
     *    PWM 频率 = 72MHz / (PSC+1) / (ARR+1) = 72000000 / 1 / 7200 = 10000Hz = 10kHz
     */
    timBase.TIM_Prescaler         = 0;
    timBase.TIM_CounterMode       = TIM_CounterMode_Up;
    timBase.TIM_Period            = MOTOR_PERIOD;
    timBase.TIM_ClockDivision     = TIM_CKD_DIV1;
    timBase.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &timBase);

    /* PWM 通道公共配置 */
    TIM_OCStructInit(&timOC);
    timOC.TIM_OCMode      = TIM_OCMode_PWM1;
    timOC.TIM_OutputState = TIM_OutputState_Enable;
    timOC.TIM_Pulse       = 0;
    timOC.TIM_OCPolarity  = TIM_OCPolarity_High;

    TIM_OC1Init(TIM2, &timOC);   /* CH1 -> PA0 左电机 */
    TIM_OC4Init(TIM2, &timOC);   /* CH4 -> PA3 右电机 */

    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM2, ENABLE);

    TIM_Cmd(TIM2, ENABLE);       /* 启动定时器 */
}

void Motor_Set(int16_t left, int16_t right)
{
    left  = Motor_Limit(left);
    right = Motor_Limit(right);

    /* 左电机：PA1=AIN1, PA2=AIN2；正值前进、负值后退 */
    if (left >= 0)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_1);
        GPIO_ResetBits(GPIOA, GPIO_Pin_2);
    }
    else
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_1);
        GPIO_SetBits(GPIOA, GPIO_Pin_2);
    }
    TIM_SetCompare1(TIM2, (uint16_t)((left >= 0) ? left : -left));

    /* 右电机：PB1=BIN1, PB8=BIN2；正值前进、负值后退 */
    if (right >= 0)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_1);
        GPIO_ResetBits(GPIOB, GPIO_Pin_8);
    }
    else
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_1);
        GPIO_SetBits(GPIOB, GPIO_Pin_8);
    }
    TIM_SetCompare4(TIM2, (uint16_t)((right >= 0) ? right : -right));
}

void Motor_Stop(void)
{
    Motor_Set(0, 0);
}
