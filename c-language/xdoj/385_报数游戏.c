#include <stdio.h>
int has_seven(int num) {
    while (num > 0) {
        if (num % 10 == 7) {
            return 1;
        }
        num /= 10;
    }
    return 0;
}

int main() {
    int n;
    scanf("%d", &n);

    int skip[3] = {0, 0, 0};
    int valid_count = 0;
    int current_num = 1;
    int player = 0;

    while (valid_count < n) {
        if (current_num % 7 == 0 || has_seven(current_num)) {
            skip[player]++;
        } else {
            valid_count++;
        }
        player = (player + 1) % 3;
        current_num++;
    }

    printf("%d %d %d\n", skip[0], skip[1], skip[2]);

    return 0;
}
