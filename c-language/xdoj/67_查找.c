#include <stdio.h>

int main() {
    int n, k;
    int a[105];

    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int found = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] == k) {
            if (found == 0) {
                printf("%d", i);
                found = 1;
            }
            else {
                printf(" %d", i);
            }
        }
    }

    if (found == 0) {
        printf("-1");
    }

    printf("\n");

    return 0;
}
