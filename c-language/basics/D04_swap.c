/*
 * D04 交换两个整数
 * 知识点：临时变量 temp 的“空杯子”思想
 * 步骤：temp=a（把 a 暂存）-> a=b（b 倒进 a）-> b=temp（暂存的 a 倒进 b）
 * 易错记录：scanf("%d %d\n",...) 格式串末尾写 \n 会导致回车后程序假死（错题 E03）
 * 输入：3 5
 * 输出：a=5 b=3
 * 日期：2026-09-28  状态：课堂验收通过
 */
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int main()
{
    int a = 0;
    int b = 0;
    int temp = 0;
    scanf("%d %d", &a, &b);

    temp = a;
    a = b;
    b = temp;

    printf("a=%d b=%d\n", a, b);
    return 0;
}
