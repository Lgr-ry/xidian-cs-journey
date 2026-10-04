#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
// XDOJ 真题 #20 四则运算（2026-10-04 AC，六组用例全部通过）
// 输入两个整数和一个运算符（+ - * / % 之一），输出和差积商余之一
// 整除及求余时除数不为零（题面保证，不输出 error）
// 样例：输入 5%2  输出（5 个前导空格）     5%2=1
int main()
{
	int a = 0;
	int b = 0;
	char op;
	int c = 0;

	scanf("%d %c %d", &a, &op, &b);

	switch (op)
	{
	case'+':
		c = a + b;
		break;
	case'-':
		c = a - b;
		break;
	case'*':
		c = a * b;
		break;
	case'/':
		c = a / b;
		break;
	case'%':
		c = a % b;
		break;
	}

	printf("     %d%c%d=%d\n", a, op, b, c);

	return 0;
}
