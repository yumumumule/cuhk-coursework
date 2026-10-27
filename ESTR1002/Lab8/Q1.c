/* L08 Q1: Memoise the recursion for one-step and two-step stair moves. */
#include <stdio.h>

static unsigned long long memo[41];

static unsigned long long climb(int stairs) {
    if (stairs <= 1) return 1;
    if (memo[stairs] == 0) memo[stairs] = climb(stairs - 1) + climb(stairs - 2);
    return memo[stairs];
}

int main(void) {
    int stairs;
    if (scanf("%d", &stairs) != 1 || stairs < 1 || stairs > 40) return 1;
    printf("%llu\n", climb(stairs));
    return 0;
}
