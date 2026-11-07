/**
 ******************************************************************************
 * @file    encoder.h
 * @brief   双路正交编码器读取（TIM3 / TIM4 硬件编码器模式，四倍频）
 ******************************************************************************
 */
#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f10x.h"

/**
 * @brief 初始化两个定时器的编码器接口。
 *        接线：左电机编码器 A/B 相 -> PA6/PA7 (TIM3)
 *              右电机编码器 A/B 相 -> PB6/PB7 (TIM4)
 */
void Encoder_Init(void);

/**
 * @brief 读取“自上次调用以来”的编码器增量，并自动清零计数。
 * @param left  返回左轮增量（前进为正，后退为负）
 * @param right 返回右轮增量
 * @note  在固定的 10ms 周期调用，读到的数值就代表本轮“速度”。
 */
void Encoder_Get(int16_t *left, int16_t *right);

#endif /* __ENCODER_H */
