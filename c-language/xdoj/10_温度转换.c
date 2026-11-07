#include<stdio.h>
int main()
{
    float F = 0;
    float C = 0;

    scanf("%f",&F);

    C = (F-32.0)*5.0/9.0;

    printf("%.2f",C);

    return 0;
}
