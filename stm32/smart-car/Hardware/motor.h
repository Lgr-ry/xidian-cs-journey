/**
 ******************************************************************************
 * @file    motor.h
 * @brief   TB6612 双直流电机驱动（TIM2 产生 2 路 PWM + 4 个方向引脚）
 ******************************************************************************
 */
#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f10x.h"

/* PWM 满量程：TIM2 自动重装值 ARR=7199，对应 100% 占空比（PWM 频率 10kHz） */
#define MOTOR_PERIOD   7199

/**
 * @brief 初始化电机相关 GPIO 与 TIM2 的 PWM 输出。
 *        接线（请勿随意更改）：
 *          左电机 A 通道：PWMA=PA0(TIM2_CH1)，AIN1=PA1，AIN2=PA2
 *          右电机 B 通道：PWMB=PA3(TIM2_CH4)，BIN1=PB1，BIN2=PB8
 *          TB6612 的 STBY 接 3.3V，所有 GND 共地
 */
void Motor_Init(void);

/**
 * @brief 同时设置左右电机转速。
 * @param left  左轮 PWM，范围 -7199 ~ +7199，正数前进、负数后退、0 刹车
 * @param right 右轮 PWM，范围同上
 */
void Motor_Set(int16_t left, int16_t right);

/**
 * @brief 两轮立即停车（刹车）。
 */
void Motor_Stop(void);

#endif /* __MOTOR_H */
