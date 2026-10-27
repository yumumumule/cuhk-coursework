/* L05 Q2: Matrix entries increase by one along each row and column. */
#include <stdio.h>

int main(void) {
    int size;
    if (scanf("%d", &size) != 1 || size < 1 || size > 10) {
        return 1;
    }
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            printf("%d%s", row + col + 1, col == size - 1 ? "\n" : ",\t");
        }
    }
    return 0;
}
