#include<stdio.h>
int main()
{
    int n,i,num;
    long long sum = 0;
    double ave;

    scanf("%d",&n);

    for(i=0; i<n; i++)
    {
        scanf("%d",&num);

        sum = sum + num;
    }

    ave = (double)sum / (double)n;

    printf("%.2f\n",ave);

    return 0;
}
