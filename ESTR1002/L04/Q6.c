/* L04 Q6: Mark odd rows and triangular-number columns. */
#include <stdio.h>

int main(void) {
    int size, special_column[101] = {0};
    if (scanf("%d", &size) != 1 || size < 1 || size > 100) {
        return 1;
    }
    for (int i = 1, column = 1; column <= size; i++, column += i) {
        special_column[column] = 1;
    }
    for (int row = 1; row <= size; row++) {
        for (int col = 1; col <= size; col++) {
            int marks = row % 2 + special_column[col];
            putchar(marks == 2 ? '@' : marks == 1 ? '#' : '.');
        }
        putchar('\n');
    }
    return 0;
}
