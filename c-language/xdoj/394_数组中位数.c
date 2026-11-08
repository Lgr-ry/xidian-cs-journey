#include <stdio.h>

int main() {
    int n;
    int a[105];

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j+1]) {
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }

    int median;
    if (n % 2 != 0) {
        median = a[n / 2];
    } else {
        median = (a[n / 2 - 1] + a[n / 2]) / 2;
    }

    printf("%d\n", median);

    return 0;
}
