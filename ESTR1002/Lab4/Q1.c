/* L04 Q1: Count occurrences of digit 1 in a non-negative integer. */
#include <stdio.h>

int main(void) {
    int number, count = 0;
    if (scanf("%d", &number) != 1) {
        return 1;
    }
    while (number > 0) {
        if (number % 10 == 1) count++;
        number /= 10;
    }
    printf("%d\n", count);
    return 0;
}
