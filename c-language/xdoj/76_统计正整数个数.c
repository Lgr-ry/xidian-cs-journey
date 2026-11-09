#include<stdio.h>
int main()
{
    int i=0, x, n=0;
    int arr[100005]={0};

    scanf("%d",&n);

    for( i=0; i<n; i++)
    {
        scanf("%d",&x);
        arr[x]++;
    }

    for( i=0; i<100005; i++)
    {
        if(arr[i]>0)
        {
            printf("%d:%d\n",i,arr[i]);
        }
    }

    return 0;
}
