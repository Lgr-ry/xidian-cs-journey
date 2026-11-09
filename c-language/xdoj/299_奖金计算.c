#include <stdio.h>

int main() {
    long  I;
    double bonus = 0.0;

    scanf("%ld", &I);


    if (I <= 100000) {
        bonus = I * 0.1;
    }
    else if (I <= 200000) {
        bonus = 10000 + (I - 100000) * 0.075;
    }
    else if (I <= 400000) {
        bonus = 17500 + (I - 200000) * 0.05;
    }
    else if (I <= 600000) {
        bonus = 27500 + (I - 400000) * 0.03;
    }
    else if (I <= 1000000) {
        bonus = 33500 + (I - 600000) * 0.015;
    }
    else {
        bonus = 39500 + (I - 1000000) * 0.01;
    }


    printf("%d\n", (int)bonus);

    return 0;
}
