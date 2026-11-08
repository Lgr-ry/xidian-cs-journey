#include<stdio.h>
int main(void)
{
    int n, t, cnt = 0;
    int i, j, sum = 0;
    int a[12] = {0};

    scanf("%d",&n);

    if( n == 0 )
    {
        printf("0\n");
        return 0;
    }

    t = n;
    while(t > 0)
    {
     cnt++;
     t = t / 10;
    }


    for( i=0; i < cnt; i++)
    {
        a[i] = n % 10;
        n = n /10;
        sum = sum + a[i];
    }

   int ok = 1;
   i = 0;
   j = cnt - 1;

   while( i<j )
   {
       if(a[i] != a[j])
       {
           ok = 0;
           break;
       }
       i++;
       j--;
   }

   if(ok)
    {printf("%d\n",sum);}
   else
    {printf("no\n");}

    return 0;
}
