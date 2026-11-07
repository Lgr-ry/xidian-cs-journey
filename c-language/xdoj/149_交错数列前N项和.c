#include<stdio.h>
int main()
{
    int n;
    double sum = 0.0;
    double sign = 1.0;

    scanf("%d",&n);

    for(int i = 1;i <= n;i++)
    {
        double term = sign * (1.0 * i / (2 * i -1));
        sum += term;
        sign = -sign;
    }

    printf("%.3f\n",sum);

    return 0;
}
