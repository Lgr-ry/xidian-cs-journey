#include <stdio.h>

int main() {
    int y, d;
    int month = 1;

    scanf("%d %d", &y, &d);

    int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
        days[2] = 29;
    }

    while (d > days[month]) {
        d = d - days[month];
        month++;
    }

    printf("%d %d\n", month, d);

    return 0;
}
