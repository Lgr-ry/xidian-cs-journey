#include <stdio.h>

int main() {
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int p;

    scanf("%d", &p);

    // 为了方便处理数字之间的空格，我们用一个标志位记录是不是第一个输出的数
    int isFirst = 1;

    // 第一段：输出下标 p+1 到 9 的元素
    for (int i = p + 1; i < 10; i++) {
        if (isFirst) {
            printf("%d", arr[i]);
            isFirst = 0;
        } else {
            printf(" %d", arr[i]);
        }
    }

    // 第二段：输出下标 0 到 p 的元素
    for (int i = 0; i <= p; i++) {
        if (isFirst) {
            printf("%d", arr[i]);
            isFirst = 0;
        } else {
            printf(" %d", arr[i]);
        }
    }

    printf("\n"); // 最后换行

    return 0;
}
