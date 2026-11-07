#include<stdio.h>
int main()
{
    int a, b, k, s, d;
    scanf("%d %d",&a, &b);

    for( k=a; k <= b; k++)
    {
        s = 0;
        for( d=1;d<=k/2; d++ )
        {
            if( k%d == 0)
            {
                s = s + d;
            }
        }
        if( s == k)
            printf("%d\n",k);
    }

    return 0;
}
