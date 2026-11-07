#include <stdio.h>

int main() {
    char c;

    for (c = 'a'; c <= 'z'; c++) {
        if (c == 'z') {
            printf("%c", c);
        } else {
            printf("%c ", c);
        }
    }

    printf("\n");

    for (c = 'z'; c >= 'a'; c--) {
        if (c == 'a') {
            printf("%c", c);
        } else {
            printf("%c ", c);
        }
    }

    printf("\n");

    return 0;
}
