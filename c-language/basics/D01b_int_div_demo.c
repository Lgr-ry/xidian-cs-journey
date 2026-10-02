/*
 * D01b 整数除法 vs 浮点除法（本机 VS 原版，课堂演示）
 * 知识点：5/2 整数相除截断为 2；5.0/2 有一方是小数，结果为 2.5
 * 输出：7 3 2 2.5
 * 日期：2026-09-24
 */
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
	int a = 5;
	int b = 2;
	printf("%d\n", a + b);
	printf("%d\n", a - b);
	printf("%d\n", a / b);
	printf("%.1f\n", 5.0 / 2);
	return 0;
}
