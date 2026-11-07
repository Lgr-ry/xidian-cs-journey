#include<stdio.h>
int main()
{
    int arr[100];
    int n , i;
    int cnt = 0;

    scanf("%d",&n);

    for(i = 0; i < n; i++)
    {
        scanf("%d",&arr[i]);}

        for(i = 1; i <= n - 2; i++)
        {
            if((arr[i+1]-arr[i])*(arr[i]-arr[i-1]) < 0)
            {
                cnt++;
            }
        }
    printf("%d\n",cnt);

    return 0;

}
