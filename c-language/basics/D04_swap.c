/*
 * D04 交换两个整数（本机 VS 原版）
 * 知识点：临时变量 temp 的"空杯子"思想
 * 易错记录：scanf 格式串末尾写 \n 导致回车后假死（错题 E03）
 * 输入：3 5   输出：交换前 a=3,b=5；交换后 a=5,b=3
 * 日期：2026-09-28  状态：课堂验收通过
 */
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
	int a = 0;
	int b = 0;

	scanf("%d %d", &a, &b);
	printf("before:a = %d ,b = %d\n", a, b);

	int temp;

	temp = a;
	a = b;
	b = temp;

	printf("after:a = %d,b = %d\n", a, b);

	return 0;
}
