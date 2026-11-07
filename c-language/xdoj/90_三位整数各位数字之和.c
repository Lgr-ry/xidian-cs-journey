#include<stdio.h>
int main()
{
    int m = 0 ;
    scanf("%d",&m);

    int a, b, c;
    a = m / 100;
    b = (m / 10) % 10;
    c = m % 10;

    int sum = 0;
    sum = a + b + c;

    printf("%d",sum);

    return 0 ;

}
