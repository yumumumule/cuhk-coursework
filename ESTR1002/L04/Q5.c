/* L04 Q5: Draw the two sloping sides and crossbar of a capital A. */
#include <stdio.h>

int main(void) {
    int size;
    if (scanf("%d", &size) != 1 || size < 1 || size % 2 == 0) {
        return 1;
    }
    int height = 2 * size + 3;
    for (int row = 1; row <= height; row++) {
        for (int col = 1; col <= height + row - 1; col++) {
            int side = col + row == height + 1 || col == height + row - 1;
            int crossbar = row == size + 2 && col > size + 2;
            putchar(side || crossbar ? '*' : '.');
        }
        putchar('\n');
    }
    return 0;
}
