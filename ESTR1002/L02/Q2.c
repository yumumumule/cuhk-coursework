/* L02 Q2: Use H = g*t*t/2 to calculate free-fall time. */
#include <math.h>
#include <stdio.h>

int main(void) {
    double height;
    if (scanf("%lf", &height) != 1 || height < 0.0) {
        return 1;
    }
    printf("%.2f\n", sqrt(2.0 * height / 9.8));
    return 0;
}
