#include <stdio.h>

int main() {
    int n;

    scanf("%d", &n);

    if (n % 2 != 0) {
        printf("-1\n");
        return 0;
    }

    int first = 1;

    for (int i = 29; i >= 1; i--) {
        if ((n >> i) & 1) {
            if (first) {
                printf("%d", 1 << i);
                first = 0;
            } else {
                printf(" %d", 1 << i);
            }
        }
    }

    printf("\n");
    return 0;
}
