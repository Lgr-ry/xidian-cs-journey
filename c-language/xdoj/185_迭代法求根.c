#include <stdio.h>
#include <math.h>

int main() {
    double a;
    scanf("%lf", &a);


    if (a == 0) {
        printf("0.00000\n");
        return 0;
    }

    double x = a;
    double prev_x;


    do {
        prev_x = x;

        x = 0.5 * (x + a / x);
    } while (fabs(x - prev_x) >= 1e-5);


    printf("%.5f\n", x);

    return 0;
}
