/* L03 Q2: Calculate monthly pay with overtime and progressive tax. */
#include <stdio.h>

int main(void) {
    double hours, gross, tax;
    if (scanf("%lf", &hours) != 1 || hours < 0.0 || hours > 500.0) {
        return 1;
    }
    if (hours <= 160.0) {
        gross = 75.5 * hours;
    } else {
        gross = 160.0 * 75.5 + (hours - 160.0) * 75.5 * 1.5;
    }
    if (gross <= 10000.0) {
        tax = 0.1 * gross;
    } else if (gross <= 13000.0) {
        tax = 1000.0 + (gross - 10000.0) * 0.16;
    } else {
        tax = 1000.0 + 480.0 + (gross - 13000.0) * 0.23;
    }
    printf("gross  = %.2f\n", gross);
    printf("tax    = %.2f\n", tax);
    printf("netpay = %.2f\n", gross - tax);
    return 0;
}
