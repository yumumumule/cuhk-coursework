/* L06 Q5: Assign the smallest possible non-leading-zero alien number. */
#include <stdio.h>

int main(void) {
    char text[61];
    int digits[128], distinct = 0;
    if (scanf("%60s", text) != 1) return 1;
    for (int i = 0; i < 128; i++) digits[i] = -1;
    for (int i = 0; text[i] != '\0'; i++) {
        unsigned char ch = (unsigned char)text[i];
        if (ch >= 128) return 1;
        if (digits[ch] < 0) {
            /* First symbol is 1, second is 0, then 2, 3, ... */
            digits[ch] = distinct == 0 ? 1 : distinct == 1 ? 0 : distinct;
            distinct++;
        }
    }
    int base = distinct < 2 ? 2 : distinct;
    unsigned long long value = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        value = value * (unsigned int)base + (unsigned int)digits[(unsigned char)text[i]];
    }
    printf("%llu\n", value);
    return 0;
}
