/*
 * D02 两个整数的四则运算
 * 知识点：变量定义、scanf 读入、+ - * / % 五个运算符
 * 关键点：整数 / 整数结果还是整数（12/5=2，小数部分被截断）；% 取余（12%5=2）
 * 输入：12 5
 * 输出：17 7 60 2 2
 * 日期：2026-09-25  状态：课堂验收通过
 */
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int main()
{
    int a = 0;
    int b = 0;
    scanf("%d %d", &a, &b);
    printf("sum=%d\n", a + b);
    printf("diff=%d\n", a - b);
    printf("product=%d\n", a * b);
    printf("quotient=%d\n", a / b);
    printf("remainder=%d\n", a % b);
    return 0;
}
