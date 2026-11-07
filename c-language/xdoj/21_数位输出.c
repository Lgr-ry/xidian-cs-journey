#include<stdio.h>
int main()
{
    int num, i, rest;
    int cnt[5];
    int arr[5] = {10000, 1000, 100, 10, 1};
    scanf("%d",&num);

    rest = num;

    for( i = 0; i < 5 ; i++)
    {
        cnt[i] = rest / arr[i];
        rest %= arr[i];
    }

    for( i = 0; i < 5; i++)
        printf("%d%c",cnt[i], i == 4 ? '\n' : ' ');

    return 0;
}
