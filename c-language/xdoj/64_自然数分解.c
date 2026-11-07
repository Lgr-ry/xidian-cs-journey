#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int current = n * n - n + 1;

    for (int i = 0; i < n; i++) {
        printf("%d", current);

        if (i < n - 1) {
            printf(" ");
        }

        current += 2;
    }

    printf("\n");

    return 0;
}
