#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);

    int prev, curr;
    int max_diff = 0;

    scanf("%d", &prev);

    for (int i = 1; i < n; i++) {
        scanf("%d", &curr);

        int diff = abs(curr - prev);

        if (diff > max_diff) {
            max_diff = diff;
        }
        prev = curr;
    }

    printf("%d\n", max_diff);

    return 0;
}
