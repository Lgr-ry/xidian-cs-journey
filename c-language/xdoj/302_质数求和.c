#include<stdio.h>
int isPrime(int n){
    if(n < 2)
    return 0;

    for(int i = 2;i * i <= n;i++){
        if(n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}
int main()
{
    int p;
    scanf("%d",&p);

    int cot = 0, sum = 0, num = 2;
    while(1)
    {
        if(isPrime(num)){
            cot++;

            if(cot >= p && cot <= p + 100){
                sum += num;
            }

            if(cot == p + 10){
                break;
            }
        }
        num++;
    }

    printf("%d\n",sum);

    return 0;
}
