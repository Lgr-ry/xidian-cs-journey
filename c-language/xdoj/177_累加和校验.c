#include <stdio.h>

int main() {
    char s[105];
    int sum = 0;

    scanf("%s", s);

    int i = 0;
    while (s[i] != '\0') {
        sum = sum + s[i];
        i++;
    }

    sum = sum % 256;

    printf("%d\n", sum);

    return 0;
}
