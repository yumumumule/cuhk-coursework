/* L10 Q2 Task 3: Store the structure and flexible array in one allocation. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int no;
    char names[][16];
} myList;

void foo(myList *bar) {
    for (int i = bar->no - 1; i >= 0; i--) printf("%s\n", bar->names[i]);
}

int main(void) {
    int count, ch;
    if (scanf("%d", &count) != 1 || count < 0) return 1;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
    myList *list = malloc(sizeof(*list) + (size_t)count * sizeof(list->names[0]));
    if (list == NULL) return 1;
    list->no = count;
    for (int i = 0; i < count; i++) {
        if (fgets(list->names[i], sizeof(list->names[i]), stdin) == NULL) {
            free(list);
            return 1;
        }
        list->names[i][strcspn(list->names[i], "\r\n")] = '\0';
    }
    /* Pass the allocated structure itself, rather than the pointer's address. */
    foo(list);
    free(list);
    return 0;
}
