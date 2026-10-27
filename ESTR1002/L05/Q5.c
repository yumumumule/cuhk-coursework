/* L05 Q5: Meet Iron Man once his Manhattan distance is within elapsed time. */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int x, y, length;
    if (scanf("%d%d%d", &x, &y, &length) != 3 || length < 0 || length > 2000) {
        return 1;
    }
    int earliest = x == 0 && y == 0 ? 0 : -1;
    for (int minute = 1; minute <= length; minute++) {
        int direction;
        if (scanf("%d", &direction) != 1) return 1;
        switch (direction) {
            case 1: x++; break;
            case 2: x--; break;
            case 3: y--; break;
            case 4: y++; break;
            default: return 1;
        }
        /* Waiting is allowed, so there is no parity restriction. */
        if (earliest < 0 && abs(x) + abs(y) <= minute) earliest = minute;
    }
    if (earliest < 0) puts("impossible");
    else printf("%d\n", earliest);
    return 0;
}
