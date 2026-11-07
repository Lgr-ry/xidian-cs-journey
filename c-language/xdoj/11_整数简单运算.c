#include<stdio.h>
int main()
{
    int a, b;
    int sum, diff, prod, quot;

    scanf("%d %d",&a, &b);

    sum = a + b;
    diff = a - b;
    prod = a * b;
    quot = a / b;

    printf("%d\n%d\n%d\n%d\n",sum, diff, prod, quot);

    return 0;
}
