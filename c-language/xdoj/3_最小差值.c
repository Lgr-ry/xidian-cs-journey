#include <stdio.h>
#include <stdlib.h>
int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n;
    int a[1005];

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    qsort(a, n, sizeof(int), cmp);

    int min_diff = 100000;
    for (int i = 1; i < n; i++) {
        int diff = a[i] - a[i - 1];
        if (diff < min_diff) {
            min_diff = diff;
        }
    }

    printf("%d\n", min_diff);
    return 0;
}
