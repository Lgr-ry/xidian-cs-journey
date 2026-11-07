/**
 ******************************************************************************
 * @file    track.c
 * @brief   8 路红光灰度模拟分时循迹模块读取实现
 *          通过 AD0/AD1/AD2 选择 74HC4051 的 8 个通道，OUT 输出模拟电压
 *          STM32 用 ADC1 通道 8(PB0) 读取，与阈值比较判断黑白
 ******************************************************************************
 */
#include "track.h"

/* 从车左到车右的 8 路权重：越靠外权重绝对值越大 */
static const int8_t s_weight[8] = { -4, -3, -2, -1, 1, 2, 3, 4 };

void Track_Init(void)
{
    GPIO_InitTypeDef gpio;
    ADC_InitTypeDef  adc;

    /* 开启 GPIOB 和 ADC1 时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_ADC1, ENABLE);

    /* AD0=PB12, AD1=PB13, AD2=PB14 推挽输出（74HC4051 通道选择） */
    gpio.GPIO_Pin   = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
    gpio.GPIO_Mode  = GPIO_Mode_Out_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &gpio);

    /* OUT=PB0 模拟输入（ADC1_IN8） */
    gpio.GPIO_Pin   = GPIO_Pin_0;
    gpio.GPIO_Mode  = GPIO_Mode_AIN;
    GPIO_Init(GPIOB, &gpio);

    /* ADC1 配置：独立模式、单次转换、软件触发、右对齐 */
    adc.ADC_Mode               = ADC_Mode_Independent;
    adc.ADC_ScanConvMode       = DISABLE;
    adc.ADC_ContinuousConvMode = DISABLE;
    adc.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None;
    adc.ADC_DataAlign          = ADC_DataAlign_Right;
    adc.ADC_NbrOfChannel       = 1;
    ADC_Init(ADC1, &adc);

    /* 配置常规通道 8（PB0），采样时间 55.5 周期，保证读数稳定 */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_55Cycles5);

    ADC_Cmd(ADC1, ENABLE);

    /* ADC 校准（必须做，否则读数不准） */
    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1));
}

uint16_t Track_ReadADC(uint8_t ch)
{
    volatile uint32_t i;

    /* 通道号 ch 的低 3 位对应 AD2 AD1 AD0 */
    if (ch & 0x01) GPIO_SetBits(GPIOB, GPIO_Pin_12);   else GPIO_ResetBits(GPIOB, GPIO_Pin_12);
    if (ch & 0x02) GPIO_SetBits(GPIOB, GPIO_Pin_13);   else GPIO_ResetBits(GPIOB, GPIO_Pin_13);
    if (ch & 0x04) GPIO_SetBits(GPIOB, GPIO_Pin_14);   else GPIO_ResetBits(GPIOB, GPIO_Pin_14);

    /* 等待 74HC4051 通道切换稳定（约几 us） */
    for (i = 0; i < 20; i++) { }

    /* 启动 ADC 转换并等待完成 */
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET) { }

    return ADC_GetConversionValue(ADC1);
}

int8_t Track_Error(void)
{
    int16_t error = 0;
    uint8_t i;

    /* 依次读 8 路，压黑的路累加权重 */
    for (i = 0; i < 8; i++)
    {
        if (Track_ReadADC(i) < TRACK_THRESHOLD)
        {
            error += s_weight[i];
        }
    }

    return (int8_t)error;
}

uint8_t Track_IsCross(void)
{
    uint8_t i, blackCount = 0;

    /* 统计压黑的路数，6 路以上认为到达横向路口 */
    for (i = 0; i < 8; i++)
    {
        if (Track_ReadADC(i) < TRACK_THRESHOLD)
        {
            blackCount++;
        }
    }

    return (blackCount >= 6) ? 1u : 0u;
}
