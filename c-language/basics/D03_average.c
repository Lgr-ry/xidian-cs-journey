/*
 * D03 三个整数的平均值（本机 VS 原版）
 * 知识点：double、%.1f、整数除法陷阱（/3.0 才能得到小数）
 * 易错记录：曾用 int 接收 + %d 打印，输出垃圾值 1431655765（错题 E02）
 * 输入：1 2 4   输出：average = 2.3
 * 日期：2026-09-25  状态：课堂验收通过
 */
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
	int a = 0;
	int b = 0;
	int c = 0;

	scanf("%d %d %d", &a, &b, &c);

	printf("average = %.1f\n", (( a + b + c ) / 3.0));

	return 0;

}
