#include<stdio.h>
int main()
{
    int a, b;
    scanf("%d %d",&a, &b);

    if(b == 2){
        if((a % 4 == 0 && a %100 != 0)|| a % 400 == 0)
            printf("29\n");
        else
            printf("28\n");
    }
    else if(b == 4 || b == 6 || b == 9 || b == 11)
        printf("30\n");
    else
        printf("31\n");

    return 0;
}
