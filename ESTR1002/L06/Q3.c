/* L06 Q3: Compare letter frequencies, ignoring case and spaces. */
#include <ctype.h>
#include <stdio.h>

int main(void) {
    int frequency[26] = {0};
    for (int line = 0; line < 2; line++) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
            ch = tolower((unsigned char)ch);
            if (ch >= 'a' && ch <= 'z') frequency[ch - 'a'] += line == 0 ? 1 : -1;
        }
    }
    for (int i = 0; i < 26; i++) {
        if (frequency[i] != 0) {
            puts("no");
            return 0;
        }
    }
    puts("yes");
    return 0;
}
