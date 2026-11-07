#include <stdio.h>
#include <math.h>
int main() {
    int n;
    scanf("%d", &n);

    int m = (int)sqrt(n);

    if (m * m == n) {
        printf("%d\n", m);
    } else {
        printf("no\n");
    }

    return 0;
}
