#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    if (n == 0) {
        printf("0\n");
        return 0;
    }

    int prev, curr;
    int count = 1;

    scanf("%d", &prev);

    for (int i = 1; i < n; i++) {
        scanf("%d", &curr);


        if (curr != prev) {
            count++;
            prev = curr;
        }
    }


    printf("%d\n", count);

    return 0;
}
