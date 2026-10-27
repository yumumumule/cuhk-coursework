/* L05 Q1: Evaluate n! / (k! * (n-k)!), with 0! = 1. */
#include <stdio.h>

static int factorial(int number) {
    int result = 1;
    for (int i = 2; i <= number; i++) result *= i;
    return result;
}

int main(void) {
    int n, k;
    if (scanf("%d%d", &n, &k) != 2 || n < 0 || n > 12 || k < 0 || k > n) {
        return 1;
    }
    printf("%d\n", factorial(n) / (factorial(k) * factorial(n - k)));
    return 0;
}
