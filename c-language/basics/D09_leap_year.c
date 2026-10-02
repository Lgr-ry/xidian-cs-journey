/*
 * D09 判断闰年（XDOJ 仿真 W4-03）
 * 知识点：逻辑运算符 &&（与）、||（或）、!=（不等于），多条件组合
 * 闰年规则：
 *   条件一（普通年）：能被 4 整除 且 不能被 100 整除   year%4==0 && year%100!=0
 *   条件二（整百年）：能被 400 整除                     year%400==0
 *   两者满足其一即为闰年
 * 易错点：1900 能被 4 整除但也能被 100 整除，条件一不成立、又不能被 400 整除 -> no
 * 测试：3037->no  2024->yes  1900->no  2000->yes
 * 日期：2026-09-30  状态：课堂验收通过（四组样例全 AC）
 */
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int main()
{
    int year = 0;
    scanf("%d", &year);

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        printf("yes\n");
    }
    else
    {
        printf("no\n");
    }
    return 0;
}
