#include <stdio.h>

int main() {
    double distance;
    int wait_time;
    double total_fee = 0.0;


    scanf("%lf %d", &distance, &wait_time);

    if (distance <= 3.0) {
        total_fee = 10.0;
    }
    else if (distance <= 10.0) {
        total_fee = 10.0 + (distance - 3.0) * 2.0;
    }
    else {
        total_fee = 10.0 + 14.0 + (distance - 10.0) * 3.0;
    }

    total_fee = total_fee + (wait_time / 5) * 2.0;

    int final_result = (int)(total_fee + 0.5);
    printf("%d\n", final_result);

    return 0;
}
