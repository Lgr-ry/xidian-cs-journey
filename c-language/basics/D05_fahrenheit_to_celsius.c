/*
 * D05 华氏温度转摄氏温度
 * 知识点：浮点公式中至少一个操作数带小数点，结果才是小数
 * 公式：C = (F - 32) * 5 / 9   （写 5.0 或 9.0，避免整数除法）
 * 边界用例：100 -> 37.8；冰点 32 -> 0.0
 * 日期：2026-09-28  状态：课堂验收通过
 */
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int main()
{
    double f = 0.0;
    scanf("%lf", &f);
    double c = (f - 32) * 5.0 / 9.0;
    printf("C=%.1f\n", c);
    return 0;
}
