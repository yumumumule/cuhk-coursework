/* L02 Q1: Convert an integer number of inches to centimetres. */
#include <stdio.h>

int main(void) {
    int inches;
    if (scanf("%d", &inches) != 1) {
        return 1;
    }
    printf("%.1f\n", 2.54 * inches);
    return 0;
}
