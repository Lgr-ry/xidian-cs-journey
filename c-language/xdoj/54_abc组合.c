#include<stdio.h>
int main()
{
    int a, b, c, n;
    scanf("%d",&n);

    for(a=1; a <= 9; a++)
    {
        for(b=0; b<=9; b++)
        {
            for(c=1; c<=9; c++)
            {
                if(101*(a+c)+20*b==n)
               {printf("%d %d %d\n",a, b, c);}
            }
        }
    }
    return 0;
}
