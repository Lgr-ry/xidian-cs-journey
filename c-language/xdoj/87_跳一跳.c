#include<stdio.h>
int main()
{
    int x, streak=0, score=0;

    while(1)
    {
        scanf("%d",&x);

        if( x==0 )
        {
            break;
        }
        else if( x==2)
        {
            streak++;
            score = streak * 2 + score;
        }
        else if( x==1 )
        {
            streak = 0;
            score++;
        }
    }

    printf("%d\n",score);

    return 0;
}
