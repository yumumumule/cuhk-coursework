/* L10 Q2 Task 2: A structure points to x fixed-width name slots. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int no;
    char (*names)[16];
} myList;

void foo(myList *bar) {
    for (int i = bar->no - 1; i >= 0; i--) printf("%s\n", bar->names[i]);
}

int main(void) {
    myList list;
    int ch;
    if (scanf("%d", &list.no) != 1 || list.no < 0) return 1;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
    if (list.no == 0) return 0;
    list.names = malloc((size_t)list.no * sizeof(*list.names));
    if (list.names == NULL) return 1;
    for (int i = 0; i < list.no; i++) {
        if (fgets(list.names[i], sizeof(list.names[i]), stdin) == NULL) {
            free(list.names);
            return 1;
        }
        list.names[i][strcspn(list.names[i], "\r\n")] = '\0';
    }
    foo(&list);
    free(list.names);
    return 0;
}
