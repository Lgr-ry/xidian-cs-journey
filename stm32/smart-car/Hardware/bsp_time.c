/**
 ******************************************************************************
 * @file    bsp_time.c
 * @brief   毫秒级系统心跳实现（查询式 SysTick，无需中断、无需改 it.c）
 ******************************************************************************
 */
#include "bsp_time.h"

/* 上电以来的毫秒计数，volatile 防止编译器优化读取 */
static volatile uint32_t s_ms = 0;

void BSP_Time_Init(void)
{
    /*
     * STM32F103 主频 72MHz。
     * 重装值 72000-1：计数 72000 个时钟 = 1/1000 秒 = 1ms。
     * CLKSOURCE=1 用内核 72MHz 时钟；ENABLE=1 启动计数；
     * 故意不设置 TICKINT（bit1），所以不产生中断。
     */
    SysTick->LOAD = 72000U - 1U;
    SysTick->VAL  = 0U;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_ENABLE_Msk;
}

void BSP_Time_Tick(void)
{
    /*
     * COUNTFLAG(bit16)：SysTick 从重装值数到 0 的那一刻硬件自动置 1，
     * 读取 CTRL 寄存器后硬件自动清 0。读到 1 就说明恰好过去了 1ms。
     */
    if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)
    {
        s_ms++;
    }
}

uint32_t BSP_Millis(void)
{
    return s_ms;
}

void BSP_DelayMs(uint32_t ms)
{
    uint32_t start = s_ms;
    /* 延时期间也持续推进心跳，保证计时准确 */
    while ((uint32_t)(s_ms - start) < ms)
    {
        BSP_Time_Tick();
    }
}
