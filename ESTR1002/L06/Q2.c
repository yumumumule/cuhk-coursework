/* L06 Q2: Run-length encoding; omit the count for single characters. */
#include <stdio.h>
#include <string.h>

int main(void) {
    char text[2003];
    if (fgets(text, sizeof(text), stdin) == NULL) return 1;
    text[strcspn(text, "\r\n")] = '\0';
    for (int i = 0; text[i] != '\0'; ) {
        int end = i + 1;
        while (text[end] == text[i]) end++;
        putchar(text[i]);
        if (end - i > 1) printf("%d", end - i);
        i = end;
    }
    putchar('\n');
    return 0;
}
