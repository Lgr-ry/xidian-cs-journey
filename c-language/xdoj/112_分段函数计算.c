#include <stdio.h>
#include <math.h>

int main() {
    double x, f;
    scanf("%lf", &x);

    if (x >= 0) {
        f = sqrt(x);
    } else {
        f = (x + 1) * (x + 1) + 2 * x + 1.0 / x;
    }

    printf("%.2f\n", f);

    return 0;
}
