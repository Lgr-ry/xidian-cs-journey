/*
 * D05 华氏温度转摄氏温度（本机 VS 原版）
 * 知识点：int 输入转 double 计算；除以 9.0 触发浮点除法
 * 公式：c = 5 * (f - 32) / 9.0
 * 边界用例：100 -> c = 37.8；32 -> c = 0.0
 * 日期：2026-09-28  状态：课堂验收通过
 */
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
	int f;
	double c;

	scanf("%d", &f);
	c = 5 * (f - 32) / 9.0;

	printf("c = %.1f\n", c);

	return 0;
}
