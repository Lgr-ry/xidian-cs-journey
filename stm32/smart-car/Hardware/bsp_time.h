/**
 ******************************************************************************
 * @file    bsp_time.h
 * @brief   毫秒级系统心跳（查询式，不占用任何中断，和任何模板都不冲突）
 ******************************************************************************
 */
#ifndef __BSP_TIME_H
#define __BSP_TIME_H

#include "stm32f10x.h"

/**
 * @brief 初始化 1ms 心跳。
 *        原理：把内核 SysTick 配成 1ms 计数一次，但不开启中断，
 *        所以不会和工程模板自带的 SysTick_Handler / Delay 冲突。
 */
void BSP_Time_Init(void);

/**
 * @brief 心跳推进函数，必须在 main 的 while(1) 里被“频繁”调用。
 *        每过 1ms，内部毫秒计数自动 +1。
 */
void BSP_Time_Tick(void);

/**
 * @brief  返回从上电到现在经过的毫秒数（约 49 天才会溢出，比赛够用）。
 */
uint32_t BSP_Millis(void);

/**
 * @brief  简单阻塞延时，单位毫秒。
 */
void BSP_DelayMs(uint32_t ms);

#endif /* __BSP_TIME_H */
