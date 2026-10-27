/* L04 Q3: Print a calendar; Sunday is weekday zero. */
#include <stdio.h>

int main(void) {
    int first_weekday, days;
    if (scanf("%d%d", &first_weekday, &days) != 2 ||
        first_weekday < 0 || first_weekday > 6 || days < 28 || days > 31) {
        return 1;
    }
    puts("Su Mo Tu We Th Fr Sa");
    for (int i = 0; i < first_weekday; i++) printf("   ");
    for (int day = 1; day <= days; day++) {
        printf("%2d", day);
        if ((day + first_weekday) % 7 == 0 || day == days) {
            putchar('\n');
        } else {
            putchar(' ');
        }
    }
    return 0;
}
