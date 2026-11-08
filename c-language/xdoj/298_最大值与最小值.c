#include<stdio.h>
int Max(int x,int y)
{
    if( x > y)
    {
        return x;
    }else{
        return y;
    }
}

int Min(int x,int y)
{
    if( x > y)
    {
        return y;
    }else{
        return x;
    }
}


int main()
{
    int a, b;
    scanf("%d %d",&a, &b);

    int s1 = (a + b) * (a + b);
    int s2 = (a - b) * (a - b);
    int s3 = a * a + b * b;
    int s4 = a * a - b * b;

    int ma = Max(Max(s1, s2), Max(s3, s4));
    int mi = Min(Min(s1, s2), Min(s3, s4));

    printf("%d %d",ma,mi);

    return 0;

}
