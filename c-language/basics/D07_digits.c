/*
 * D07 拆分三位数的百位、十位、个位（本机 VS 原版）
 * 知识点：/ 整除与 % 取余配合拆数位；shi = (a/10)%10 可推广到更高位
 * 边界用例：105 -> bai=1, shi=0, ge=5
 * 日期：2026-09-28  状态：课堂验收通过
 */
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
	int a;
	scanf("%d", &a);

	int bai = a / 100;
	int ge = a % 10;
	int shi= (a / 10) % 10;

	printf("bai=%d, shi=%d, ge=%d\n", bai,shi,ge);

	return 0;
}
