#include<stdio.h>
int main()
{
    int wage, i, rest;
    int arr[]={100, 50, 20, 10, 5, 1};
    int cnt[6];

    scanf("%d",&wage);
    rest = wage;

    for(i = 0; i < 6; i++)
    {
        cnt[i] = rest / arr[i];
        rest %= arr[i];
    }

    for (i = 0; i <6; i++)
        printf("%d%c",cnt[i], i == 5 ? '\n': ' ');

    return 0;
}
