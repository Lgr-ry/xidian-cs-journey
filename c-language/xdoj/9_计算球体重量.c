#include <stdio.h>

#define PI 3.1415926

int main() {
    int d_iron, d_gold;


    scanf("%d %d", &d_iron, &d_gold);


    double r_iron = d_iron / 20.0;
    double r_gold = d_gold / 20.0;

    double v_iron = (4.0 / 3.0) * PI * r_iron * r_iron * r_iron;
    double v_gold = (4.0 / 3.0) * PI * r_gold * r_gold * r_gold;


    double m_iron = 7.86 * v_iron;
    double m_gold = 19.3 * v_gold;


    printf("%.3f %.3f\n", m_iron, m_gold);

    return 0;
}
