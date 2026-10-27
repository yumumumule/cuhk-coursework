/* L02 Q4: Print a four-bit binary number, including leading zeroes. */
#include <stdio.h>

int main(void) {
    int number;
    if (scanf("%d", &number) != 1 || number < 0 || number > 15) {
        return 1;
    }
    printf("%d%d%d%d\n", number / 8, number / 4 % 2,
           number / 2 % 2, number % 2);
    return 0;
}
