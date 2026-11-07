#include <stdio.h>

int main() {
    int S;
    int A;
    int tax = 0;

    scanf("%d", &S);

    A = S - 3500;

    if (A <= 0) {
        tax = 0;
    }
    else if (A <= 1500) {
        tax = A * 3 / 100;
    }
    else if (A <= 4500) {
        tax = 45 + (A - 1500) * 10 / 100;
    }
    else if (A <= 9000) {
        tax = 345 + (A - 4500) * 20 / 100;
    }
    else if (A <= 35000) {
        tax = 1245 + (A - 9000) * 25 / 100;
    }
    else {
        tax = 7745 + (A - 35000) * 30 / 100;
    }

    printf("%d\n", S - tax);

    return 0;
}
