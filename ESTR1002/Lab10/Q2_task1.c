/* L10 Q2 Task 1: Allocate exactly x name pointers and x small strings. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void foo(char **names, int x) {
    for (int i = x - 1; i >= 0; i--) printf("%s\n", names[i]);
}

int main(void) {
    int count, ch;
    if (scanf("%d", &count) != 1 || count < 0) return 1;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
    if (count == 0) return 0;
    char **names = calloc((size_t)count, sizeof(*names));
    if (names == NULL) return 1;
    int status = 0;
    for (int i = 0; i < count; i++) {
        names[i] = malloc(16);
        if (names[i] == NULL || fgets(names[i], 16, stdin) == NULL) {
            status = 1;
            break;
        }
        names[i][strcspn(names[i], "\r\n")] = '\0';
    }
    if (status == 0) foo(names, count);
    for (int i = 0; i < count; i++) free(names[i]);
    free(names);
    return status;
}
