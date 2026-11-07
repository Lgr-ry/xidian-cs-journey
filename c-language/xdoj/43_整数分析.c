#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    if (n == 0) {
        printf("1 0 0\n");
        return 0;
    }

    int count = 0;
    int max_digit = -1;
    int min_digit = 10;

    while (n > 0) {
        int digit = n % 10;

        count++;

        if (digit > max_digit) {
            max_digit = digit;
        }
        if (digit < min_digit) {
            min_digit = digit;
        }

        n = n / 10;
    }

    printf("%d %d %d\n", count, max_digit, min_digit);

    return 0;
}
