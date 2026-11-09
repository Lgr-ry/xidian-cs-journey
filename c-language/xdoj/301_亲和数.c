#include<stdio.h>
int get_sum_and_count(int num, int *count) {
    int sum = 0;
    *count = 0;
    if (num > 1) {
        sum += 1;
        (*count)++;
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            sum += i;
            (*count)++;
            if (i * i != num) {
                sum += num / i;
                (*count)++;
            }
        }
    }
    return sum;
}
int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int count_n, count_m;
    int sum_n = get_sum_and_count(n, &count_n);
    int sum_m = get_sum_and_count(m, &count_m);


    if (sum_n == m && sum_m == n) {
        printf("yes %d %d\n", count_n, count_m);
    } else {
        printf("no %d %d\n", count_n, count_m);
    }

    return 0;
}
