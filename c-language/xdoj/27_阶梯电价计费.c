#include<stdio.h>
int main()
{
    double x, y;
    scanf("%lf",&x);

    if(0.0 <= x && x <=110.0)
    {
        y = x * 0.5;
    }
    else if(x <= 210.0)
    {
        y = 55 + (x - 110.0)*0.55;
    }
    else if(x > 210.0)
    {
        y = 55 + 55 + (x - 210.0)*0.70;
    }

    printf("%.2f\n",y);
    return 0;
}
