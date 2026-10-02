/*
 * D04' 三个数轮换（D04 的变形）
 * 知识点：临时变量思想推广到三个变量
 * 要求：输入 1 2 3，让 a 拿到 c 的值、b 拿到 a 的值、c 拿到 b 的值
 * 输入：1 2 3
 * 输出：a=3 b=1 c=2
 * 日期：2026-09-28  状态：课堂验收通过
 */
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int main()
{
    int a = 0;
    int b = 0;
    int c = 0;
    int temp = 0;
    scanf("%d %d %d", &a, &b, &c);

    temp = a;   /* 先把 a 存起来 */
    a = c;      /* a 拿到 c 的值 */
    c = b;      /* c 拿到 b 的值 */
    b = temp;   /* b 拿到原来 a 的值 */

    printf("a=%d b=%d c=%d\n", a, b, c);
    return 0;
}
