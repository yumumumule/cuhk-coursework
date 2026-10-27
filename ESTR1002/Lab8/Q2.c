/* L08 Q2: Count paths with arbitrary-length rightward or upward moves. */
#include <stdio.h>

static unsigned long long memo[10][10];

static unsigned long long ways(int x, int y) {
    if (x == 0 && y == 0) return 1;
    if (memo[x][y] != 0) return memo[x][y];
    unsigned long long total = 0;
    for (int i = 0; i < x; i++) total += ways(i, y);
    for (int j = 0; j < y; j++) total += ways(x, j);
    memo[x][y] = total;
    return total;
}

int main(void) {
    printf("%llu\n", ways(9, 9));
    return 0;
}
