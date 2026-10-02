/*
 * D08 两个整数求最大值（本机 VS 原版）
 * 知识点：if / else 分支、关系运算符 >=（覆盖两数相等）
 * 输入：3 7 / 9 2 / 5 5   输出：max=7 / max=9 / max=5
 * 日期：2026-09-28  状态：课堂验收通过
 */
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
	int a;
	int b;

	scanf("%d %d", &a, &b);

	if (a >= b) {
		printf("max=%d\n", a);
	}
	else {
		printf("max=%d\n", b);
	}
	return 0;
}
