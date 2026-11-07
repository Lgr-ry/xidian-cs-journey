/**
 ******************************************************************************
 * @file    encoder.c
 * @brief   双路正交编码器读取实现（TIM3 / TIM4 四倍频硬件计数）
 ******************************************************************************
 */
#include "encoder.h"

/*
 * 方向校正系数：装好车后，如果发现某个轮子“前进时读数反而是负数”，
 * 只需要把对应方向改成 -1 即可（也可以直接对调该电机的两根编码器线）。
 */
#define ENC_LEFT_DIR    1
#define ENC_RIGHT_DIR   1

void Encoder_Init(void)
{
    GPIO_InitTypeDef        gpio;
    TIM_TimeBaseInitTypeDef timBase;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4, ENABLE);

    /* 编码器 A/B 相引脚：浮空输入（由编码器/电机霍尔端主动输出高低电平） */
    gpio.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;

    gpio.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7;   /* 左：PA6/PA7 -> TIM3 */
    GPIO_Init(GPIOA, &gpio);

    gpio.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7;   /* 右：PB6/PB7 -> TIM4 */
    GPIO_Init(GPIOB, &gpio);

    /* 定时器 16 位自由计数：PSC 不分频，ARR 给满 */
    timBase.TIM_Prescaler         = 0;
    timBase.TIM_CounterMode       = TIM_CounterMode_Up;
    timBase.TIM_Period            = 65535;
    timBase.TIM_ClockDivision     = TIM_CKD_DIV1;
    timBase.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &timBase);
    TIM_TimeBaseInit(TIM4, &timBase);

    /*
     * TI12 编码器模式：A、B 两相都参与计数，相当于四倍频，
     * 正转自动加数、反转自动减数。
     */
    TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,
                               TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,
                               TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

    TIM_SetCounter(TIM3, 0);
    TIM_SetCounter(TIM4, 0);
    TIM_Cmd(TIM3, ENABLE);
    TIM_Cmd(TIM4, ENABLE);
}

void Encoder_Get(int16_t *left, int16_t *right)
{
    int16_t l = (int16_t)TIM_GetCounter(TIM3);   /* 强转 int16_t 自动处理 65535 溢出回绕 */
    int16_t r = (int16_t)TIM_GetCounter(TIM4);

    TIM_SetCounter(TIM3, 0);                     /* 读完清零，下次读到的就是新增量 */
    TIM_SetCounter(TIM4, 0);

    *left  = (int16_t)(l * ENC_LEFT_DIR);
    *right = (int16_t)(r * ENC_RIGHT_DIR);
}
