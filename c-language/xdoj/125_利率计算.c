#include<stdio.h>
int main()
{
    double r, n, p = 1.0;
    scanf("%lf %lf",&r, &n);

    int i = 0;

    for(i = 0; i < n; i++)
    {
        p = p * ( 1 + r);
    }

    printf("%.2f\n",p);

    return 0;
}
