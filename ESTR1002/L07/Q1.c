/* L07 Q1: Decode one-based character indices from a paragraph. */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char text[203];
    if (fgets(text, sizeof(text), stdin) == NULL) return 1;
    text[strcspn(text, "\r\n")] = '\0';
    size_t length = strlen(text);
    char indices[1003];
    if (fgets(indices, sizeof(indices), stdin) == NULL) return 1;
    char *cursor = indices;
    while (*cursor != '\0') {
        while (isspace((unsigned char)*cursor)) cursor++;
        if (*cursor == '\0') break;
        char *end;
        long index = strtol(cursor, &end, 10);
        if (end == cursor || index < 1 || (size_t)index > length) return 1;
        putchar(tolower((unsigned char)text[index - 1]));
        cursor = end;
    }
    putchar('\n');
    return 0;
}
