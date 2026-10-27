/* L06 Q1: Require a digit, both letter cases and an allowed punctuation mark. */
#include <stdio.h>
#include <string.h>

int main(void) {
    char password[31];
    const char *punctuation = ".;:()<>{}[]\"?~!`'&%#|\\/";
    int upper = 0, lower = 0, digit = 0, symbol = 0;
    if (scanf("%30s", password) != 1) return 1;
    for (int i = 0; password[i] != '\0'; i++) {
        char ch = password[i];
        if (ch >= 'A' && ch <= 'Z') upper = 1;
        if (ch >= 'a' && ch <= 'z') lower = 1;
        if (ch >= '0' && ch <= '9') digit = 1;
        if (strchr(punctuation, ch) != NULL) symbol = 1;
    }
    puts(upper && lower && digit && symbol ? "yes" : "no");
    return 0;
}
