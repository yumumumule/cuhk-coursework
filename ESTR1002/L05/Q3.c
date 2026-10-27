/* L05 Q3: Find all equilibrium indices in O(n) time. */
#include <stdio.h>

#define CAPACITY 20000

int main(void) {
    int length, values[CAPACITY], found = 0;
    long long left = 0, right = 0;
    if (scanf("%d", &length) != 1 || length < 3 || length > CAPACITY) {
        return 1;
    }
    for (int i = 0; i < length; i++) {
        if (scanf("%d", &values[i]) != 1) return 1;
        right += values[i];
    }
    for (int i = 0; i < length; i++) {
        /* Remove the current value before comparing the two sides. */
        right -= values[i];
        if (left == right) {
            printf("%s%d", found ? " " : "", i);
            found = 1;
        }
        left += values[i];
    }
    if (!found) printf("-1");
    putchar('\n');
    return 0;
}
