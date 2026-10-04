#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
// D10 switch 简易计算器（教学版）
// 输入：整数 运算符 整数（支持 + - * /）
// 输出：回显算式与结果；除数为 0 或非法运算符输出 error
// 2026-10-04：六组用例全部通过（3+5=8 / 10-4=6 / 6*7=42 / 8/2=4 / 5/0->error / 非法符->error）
int main()
{
	int a = 0;
	int b = 0;
	char op;

	scanf("%d %c %d", &a, &op, &b);

	int c = 0;

	switch (op)
	{
	case '+':
		c = a + b;
		printf("%d%c%d=%d\n", a, op, b, c);
		break;
	case '-':
		c = a - b;
		printf("%d%c%d=%d\n", a, op, b, c);
		break;
	case '*':
		c = a * b;
		printf("%d%c%d=%d\n", a, op, b, c);
		break;
	case '/':
		if (b == 0)
			printf("error");
		else {
			c = a / b;
			printf("%d%c%d=%d\n", a, op, b, c);
		}
		break;
	default:
		printf("error");
		break;
	}

	return 0;
}
