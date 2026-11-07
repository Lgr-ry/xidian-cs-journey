/**
 ******************************************************************************
 * @file    uart.h
 * @brief   USART1 串口初始化 + printf 重定向（把数据发到电脑串口助手）
 ******************************************************************************
 */
#ifndef __UART_H
#define __UART_H

#include "stm32f10x.h"
#include <stdio.h>

/**
 * @brief 初始化串口 1。
 * @param baud 波特率，例如 115200
 * @note 接线：PA9=TXD 接 USB转串口模块的 RXD；
 *             PA10=RXD 接模块的 TXD；GND 与模块共地。
 *       想用 printf 必须在 Keil 里勾选 "Use MicroLIB"（见知识书）。
 */
void UART_Init(uint32_t baud);

#endif /* __UART_H */
