/* L04 Q4: Draw the diagonals and centre lines of a star. */
#include <stdio.h>

int main(void) {
    int size;
    if (scanf("%d", &size) != 1 || size < 1 || size % 2 == 0) {
        return 1;
    }
    int width = 2 * size + 1;
    for (int row = 0; row < width; row++) {
        for (int col = 0; col < width; col++) {
            putchar(row == col || row == size || col == size ||
                    row + col == width - 1 ? 'x' : '.');
        }
        putchar('\n');
    }
    return 0;
}
