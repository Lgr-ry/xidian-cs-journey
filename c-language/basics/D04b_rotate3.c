/*
 * D04' 三个数轮换（本机 VS 原版，双临时变量写法）
 * 知识点：temp 思想推广；temp1 存 a、temp2 存 b，再依次赋值
 * 输入：1 2 3   输出：after :a=3, b=1, c=2
 * 日期：2026-09-28  状态：课堂验收通过
 */
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
	int a = 0;
	int b = 0;
	int c = 0;

	scanf("%d %d %d", &a, &b, &c);
	printf("before:a=%d, b=%d, c=%d\n", a, b, c);

	int temp1;
	int temp2;

	temp1 = a;
	temp2 = b;
	a = c;
	b = temp1;
	c = temp2;

	printf("after :a=%d, b=%d, c=%d\n", a, b, c);

	return 0;
}
