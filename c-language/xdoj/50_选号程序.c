#include <stdio.h>

int getSum(int num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int main() {
    int n;
    scanf("%d", &n);

    int best_num = 0;
    int best_sum = -1;
    for (int i = 0; i < n; i++) {
        int current_num;
        scanf("%d", &current_num);

        int current_sum = getSum(current_num);

        if (current_sum > best_sum) {
            best_sum = current_sum;
            best_num = current_num;
        }
        else if (current_sum == best_sum) {
            if (current_num > best_num) {
                best_num = current_num;
            }
        }
    }

    printf("%d\n", best_num);

    return 0;
}
