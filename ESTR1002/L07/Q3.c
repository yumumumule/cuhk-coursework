/* L07 Q3: Estimate pi using the fraction of points inside a circle. */
#include <stdio.h>
#include <stdlib.h>

#ifndef SAMPLES
#define SAMPLES 100000000
#endif

int main(void) {
    long long inside = 0;
    /* A fixed seed makes repeated runs reproducible on the same C runtime. */
    srand(1);
    for (long long i = 0; i < SAMPLES; i++) {
        double x = (rand() + 0.5) / (RAND_MAX + 1.0) - 0.5;
        double y = (rand() + 0.5) / (RAND_MAX + 1.0) - 0.5;
        if (x * x + y * y <= 0.25) inside++;
    }
    printf("%.6f\n", 4.0 * (double)inside / SAMPLES);
    return 0;
}
