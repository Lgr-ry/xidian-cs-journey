/*
 * D06 小写字母转大写字母（本机 VS 原版，XDOJ 仿真 W4-02）
 * 知识点：char 本质是 1 字节整数、ASCII、字符算术
 * 易错记录（错题 E04）：两个占位符没看同一个值，输出 "a 65"；
 *           先把转换结果存进 upper，两个占位符统一打印 upper
 * 输入：m / j / a / z   输出：M 77 / J 74 / A 65 / Z 90
 * 日期：2026-09-29  状态：课堂验收通过（含 a/z 边界）
 */
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
	char ch;
	scanf("%c", &ch);

	char upper=0;
	upper = ch - 'a' + 'A';

	printf("%c %d\n",upper,upper);

	return 0;
}
