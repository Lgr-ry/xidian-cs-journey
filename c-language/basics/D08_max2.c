/*
 * D08 两个整数求最大值
 * 知识点：if / else 分支、关系运算符 >=
 * 边界用例：两数相等时（5 5）输出 5，条件用 >= 覆盖相等情况
 * 输入：3 7 / 9 2 / 5 5
 * 输出：max=7 / max=9 / max=5
 * 日期：2026-09-28  状态：课堂验收通过
 */
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int main()
{
    int a = 0;
    int b = 0;
    scanf("%d %d", &a, &b);

    if (a >= b)
    {
        printf("max=%d\n", a);
    }
    else
    {
        printf("max=%d\n", b);
    }
    return 0;
}
