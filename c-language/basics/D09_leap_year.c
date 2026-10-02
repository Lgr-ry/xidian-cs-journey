/*
 * D09 判断闰年（本机 VS 原版，XDOJ 仿真 W4-03）
 * 知识点：逻辑与 &&、逻辑或 ||、多条件组合
 * 规则：普通年 year%4==0 && year%100!=0；整百年 year%400==0；满足其一即可
 * 测试：3037->no  2024->yes  1900->no  2000->yes
 * 日期：2026-09-30  状态：四组样例全 AC，口头迁移通过
 */
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
	int year = 0;

	scanf("%d", &year);

	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
	{
		printf("yes\n");
	}
	else {
		printf("no\n");
	}

	return 0;
}
