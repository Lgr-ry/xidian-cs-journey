/*
 * D07 拆分三位数的百位、十位、个位
 * 知识点：/ 整除 和 % 取余 配合拆数位
 * 规律：百位 = n/100；个位 = n%10；十位 = (n/10)%10（可推广到更高位数）
 * 边界用例：105 -> bai=1, shi=0, ge=5（中间带 0 也要正确）
 * 日期：2026-09-28  状态：课堂验收通过
 */
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int main()
{
    int a = 0;
    scanf("%d", &a);

    int bai = a / 100;
    int ge = a % 10;
    int shi = (a / 10) % 10;

    printf("bai=%d, shi=%d, ge=%d\n", bai, shi, ge);
    return 0;
}
