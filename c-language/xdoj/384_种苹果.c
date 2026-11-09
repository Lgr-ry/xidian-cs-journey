#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int t;
    scanf("%d", &t);
    int current = t;

    int max_drop = -1;
    int max_round = 1;

    for (int i = 1; i <= n; i++) {
        int drop;
        scanf("%d", &drop);

        current = current + drop;

        int amount = -drop;

        if (amount > max_drop) {
            max_drop = amount;
            max_round = i;
        }
    }

    printf("%d %d\n", current, max_round);

    return 0;
}
