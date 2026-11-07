#include <stdio.h>

int main() {
    int a, b;
    char op;
    int result;

    scanf("%d%c%d", &a, &op, &b);

    switch (op) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            result = a / b;
            break;
        case '%':
            result = a % b;
            break;
    }

    printf("%d%c%d=%d\n", a, op, b, result);

    return 0;
}
