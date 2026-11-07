#include<stdio.h>
int main()
{
    int num = 0;
    scanf("%d",&num);

    if(num % 2 == 0)
        printf("偶数\n");
    else
        printf("奇数\n");

    return 0;
}
