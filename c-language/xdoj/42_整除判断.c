#include<stdio.h>
int main()
{
    int a = 0, b = 0;
    int m = 0, n = 0;

    scanf("%d %d",&a, &b);

    m = a / b;
    n = a % b;

    if( n == 0 && m != 0)
        printf("yes\n");
    else
        printf("%d %d", m , n );

    return 0;
}
