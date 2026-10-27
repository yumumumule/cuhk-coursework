/* L10 Q3: Fill a large static array and print its maximum. */
#include "func.h"
#include <stdlib.h>
#include <time.h>

/* Static storage avoids putting the 100-million-element array on the stack. */
static struct foo bar;

int main(void) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < SIZE; i++) bar.a[i] = rand();
    func(bar.a);
    return 0;
}
