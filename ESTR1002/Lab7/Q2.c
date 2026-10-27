/* L07 Q2: A UTF-8 character is a string of bytes, not one C char. */
#include <stdio.h>

int main(void) {
    /* U+65E5 (日) encoded explicitly in UTF-8, independent of source encoding. */
    puts("\xE6\x97\xA5");
    printf("\101\n");
    return 0;
}
