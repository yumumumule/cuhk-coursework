/* L03 Q3: Calculate a journey duration, including overnight journeys. */
#include <stdio.h>

int main(void) {
    int departure, arrival;
    if (scanf("%d%d", &departure, &arrival) != 2) {
        return 1;
    }
    int start = departure / 100 * 60 + departure % 100;
    int finish = arrival / 100 * 60 + arrival % 100;
    int duration = finish - start;
    /* The specified range is 1..1440, so equal times mean 24 hours. */
    if (duration <= 0) {
        duration += 24 * 60;
    }
    printf("%d\n", duration);
    return 0;
}
