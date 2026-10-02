/*
 * D06 小写字母转大写字母（XDOJ 仿真 W4-02）
 * 知识点：char 本质是 1 字节整数、ASCII 码、字符可以参与算术运算
 * 原理：大写字母 = 小写字母 - 'a' + 'A'（大小写字母 ASCII 相差固定值 32）
 * 易错记录（错题 E04）：printf("%c %d", ch, ch-'a'+'A') 两个占位符看的不是
 *           同一个值，导致输出 "a 65"（字母没变大写、编号已是大写编号）；
 *           正确做法是先把转换结果存进变量 upper，两个占位符都打印 upper。
 * 输入：m / j / a / z
 * 输出：M 77 / J 74 / A 65 / Z 90
 * 日期：2026-09-29  状态：课堂验收通过（含 a/z 边界）
 */
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int main()
{
    char ch = 0;
    scanf("%c", &ch);

    char upper = 0;
    upper = ch - 'a' + 'A';

    printf("%c %d\n", upper, upper);
    return 0;
}
