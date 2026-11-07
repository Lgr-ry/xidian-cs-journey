#include<stdio.h>
#define Max(x,y)((x)>(y) ? (x):(y))

int main()
{
    int a, b, c, d;
    scanf("%d %d %d %d",&a, &b, &c, &d);

    int m = Max(Max(a,b),Max(c,d));
    printf("%d\n",m);

    return 0;

}
