#include<stdio.h>
int main()
{
    int n,i,x,num = 0;
    int c1 = 0,c2 = 0,c3 = 0,c4 = 0,c5 = 0,c6 = 0;

    scanf("%d",&n);

    for(i = 0;i < n;i++)
    {
        scanf("%d",&x);
        num = num + x;

        if(0 <= x && x <= 50)
            c1++;
        else if(x <= 100)
            c2++;
        else if(x <= 150)
            c3++;
        else if(x <= 200)
            c4++;
        else if(x <= 300)
            c5++;
        else if(x > 300)
            c6++;
    }

    printf("%.2f\n%d %d %d %d %d %d",(double)num/n,c1,c2,c3,c4,c5,c6);

    return 0;
}
