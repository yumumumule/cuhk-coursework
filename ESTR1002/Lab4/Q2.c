/* L04 Q2: Print a decreasing triangle with comma-separated numbers. */
#include <stdio.h>

int main(void) {
    int size;
    if (scanf("%d", &size) != 1 || size < 1 || size > 15) {
        return 1;
    }
    for (int row = size; row >= 1; row--) {
        for (int value = row; value >= 1; value--) {
            printf("%d%s", value, value == 1 ? "\n" : ",");
        }
    }
    return 0;
}
