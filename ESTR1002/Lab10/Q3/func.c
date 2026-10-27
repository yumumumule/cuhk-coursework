/* L10 Q3: Scan every element, including the last, using pointer arithmetic. */
#include "func.h"
#include <stdio.h>

void func(int a[]) {
    const int *maximum = a;
    for (const int *current = a + 1; current < a + SIZE; current++) {
        if (*current > *maximum) maximum = current;
    }
    printf("%d\n", *maximum);
}
