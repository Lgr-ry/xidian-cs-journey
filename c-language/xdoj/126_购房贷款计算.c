#include<stdio.h>
#include<math.h>
int main()
{
    double d, p, r, m;

    scanf("%lf %lf %lf",&d, &p, &r);

    m = (log(p) - log(p - d * r)) / log( 1.0 + r );

    printf("%.2f\n",m);

    return 0;
}
