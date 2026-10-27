/* L05 Q4: Sum strict local maxima and minima; plateaus do not count. */
#include <stdio.h>

#define CAPACITY 2000

int main(void) {
    int length, values[CAPACITY];
    long long sum = 0;
    if (scanf("%d", &length) != 1 || length < 1 || length > CAPACITY) {
        return 1;
    }
    for (int i = 0; i < length; i++) {
        if (scanf("%d", &values[i]) != 1) return 1;
    }
    for (int i = 1; i + 1 < length; i++) {
        if ((values[i] > values[i - 1] && values[i] > values[i + 1]) ||
            (values[i] < values[i - 1] && values[i] < values[i + 1])) {
            sum += values[i];
        }
    }
    printf("%lld\n", sum);
    return 0;
}
