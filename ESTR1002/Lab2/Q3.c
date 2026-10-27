/* L02 Q3: Weight the four binary digits by 8, 4, 2 and 1. */
#include <stdio.h>

int main(void) {
    int binary;
    if (scanf("%d", &binary) != 1) {
        return 1;
    }
    int a = binary / 1000 % 10;
    int b = binary / 100 % 10;
    int c = binary / 10 % 10;
    int d = binary % 10;
    printf("%d\n", a * 8 + b * 4 + c * 2 + d);
    return 0;
}
