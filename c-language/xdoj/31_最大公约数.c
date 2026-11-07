#include<stdio.h>
int main()
{
    int a, b;
    int temp;

    scanf("%d %d",&a,&b);

    while( b != 0)
    {
        temp = a % b;
        a = b;
        b = temp;
    }

    printf("%d\n",a);

    return 0;
}
