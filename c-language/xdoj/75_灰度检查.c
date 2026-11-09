#include<stdio.h>
int main()
{
    int m,n,i=0,x=0;
    int cnt[16]={0};

    scanf("%d %d",&m,&n);

    for( i=0; i<m*n; i++ )
    {
        scanf("%d",&x);
        cnt[x]++;

    }

    for( i=0; i<16; i++)
    {
        if(cnt[i]>0)
        {
            printf("%d %d\n",i,cnt[i]);
        }
    }

    return 0;

}
