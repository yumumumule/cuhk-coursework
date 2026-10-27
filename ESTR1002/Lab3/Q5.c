/* L03 Q5: Solve a*base^2 + b*base + c = decimal for an integer base. */
#include <math.h>
#include <stdio.h>

int main(void) {
    int decimal, alien;
    if (scanf("%d%d", &decimal, &alien) != 2) {
        return 1;
    }
    int a = alien / 100;
    int b = alien / 10 % 10;
    int c = alien % 10;
    int largest_digit = a > b ? a : b;
    if (c > largest_digit) largest_digit = c;
    int smallest_base = largest_digit + 1;
    if (smallest_base < 2) smallest_base = 2;

    int base = smallest_base;
    if (a != 0) {
        double discriminant = (double)b * b + 4.0 * a * (decimal - c);
        if (discriminant < 0.0) {
            puts("CHEATED");
            return 0;
        }
        base = (int)round((-b + sqrt(discriminant)) / (2.0 * a));
    } else if (b != 0) {
        base = (decimal - c) / b;
    }
    /* Exact substitution rejects fractional roots and invalid base digits. */
    if (base >= smallest_base && a * base * base + b * base + c == decimal) {
        printf("%d\n", base);
    } else {
        puts("CHEATED");
    }
    return 0;
}
