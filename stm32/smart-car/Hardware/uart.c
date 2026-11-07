/**
 ******************************************************************************
 * @file    uart.c
 * @brief   USART1 初始化与 printf 重定向实现（标准外设库）
 ******************************************************************************
 */
#include "uart.h"

void UART_Init(uint32_t baud)
{
    GPIO_InitTypeDef  gpio;
    USART_InitTypeDef usart;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

    /* PA9(TX)：复用推挽输出 */
    gpio.GPIO_Pin   = GPIO_Pin_9;
    gpio.GPIO_Mode  = GPIO_Mode_AF_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio);

    /* PA10(RX)：浮空输入 */
    gpio.GPIO_Pin   = GPIO_Pin_10;
    gpio.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &gpio);

    USART_StructInit(&usart);
    usart.USART_BaudRate            = baud;
    usart.USART_WordLength          = USART_WordLength_8b;     /* 8 位数据 */
    usart.USART_StopBits            = USART_StopBits_1;        /* 1 位停止 */
    usart.USART_Parity              = USART_Parity_No;         /* 无校验 */
    usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    usart.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &usart);

    USART_Cmd(USART1, ENABLE);
}

/*
 * 重定向标准库 printf 到串口 1。
 * 在 Keil 勾选 Use MicroLIB 后，只需实现这一个 fputc 即可使用 printf。
 */
int fputc(int ch, FILE *f)
{
    (void)f;  /* 避免“未使用参数”警告 */

    USART_SendData(USART1, (uint8_t)ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
    {
        ;  /* 等待发送数据寄存器为空，确保一个字节发完 */
    }
    return ch;
}
