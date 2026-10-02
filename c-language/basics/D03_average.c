/*
 * D03 三个整数的平均值
 * 知识点：double 类型、%.1f 占位符、整数除法陷阱
 * 易错记录：用 int 接收平均值 + %d 打印 double，输出垃圾值 1431655765（错题 E02）；
 *           (a+b+c)/3 是整数除法，必须写 /3.0 让结果变成小数
 * 输入：1 2 4
 * 输出：average=2.3
 * 日期：2026-09-25  状态：课堂验收通过
 */
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int main()
{
    int a = 0;
    int b = 0;
    int c = 0;
    scanf("%d %d %d", &a, &b, &c);
    double average = (a + b + c) / 3.0;
    printf("average=%.1f\n", average);
    return 0;
}
