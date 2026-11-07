#include<stdio.h>
int main()
{
    int a,b,c,x,banned=0;

    scanf("%d %d %d",&a,&b,&c);
    x = c % 10;

    if(a>=1 && a<=5 && b>=200){
        if(b<400)
        {
            if(a == 1)           banned = (x == 1 || x == 6);
                else if(a == 2) banned = (x == 2 || x == 7);
                else if(a == 3) banned = (x == 3 || x == 8);
                else if(a == 4) banned = (x == 4 || x == 9);
                else if(a == 5) banned = (x == 5 || x == 0);
        }
        else
        {
            if(a == 1 || a == 3 || a == 5 )  banned = ( x % 2 == 1);
            else banned = ( x % 2 == 0);
        }
    }

    printf("%d %s\n",x ,banned ? "yes" : "no");

    return 0;
}
