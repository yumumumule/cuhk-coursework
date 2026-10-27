/* L09 Q2: Levenshtein distance with insertions, deletions and substitutions. */
#include <stdio.h>
#include <string.h>

static int minimum(int a, int b, int c) {
    int smaller = a < b ? a : b;
    return smaller < c ? smaller : c;
}

int main(void) {
    /* Leave room for ten characters, CR/LF and the terminating null. */
    char first[13], second[13];
    if (fgets(first, sizeof(first), stdin) == NULL ||
        fgets(second, sizeof(second), stdin) == NULL) return 1;
    first[strcspn(first, "\r\n")] = '\0';
    second[strcspn(second, "\r\n")] = '\0';
    int n = (int)strlen(first), m = (int)strlen(second);
    if (n > 10 || m > 10) return 1;
    int distance[11][11];
    for (int i = 0; i <= n; i++) distance[i][0] = i;
    for (int j = 0; j <= m; j++) distance[0][j] = j;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int substitution = first[i - 1] != second[j - 1];
            distance[i][j] = minimum(distance[i - 1][j] + 1,
                                     distance[i][j - 1] + 1,
                                     distance[i - 1][j - 1] + substitution);
        }
    }
    printf("%d\n", distance[n][m]);
    return 0;
}
