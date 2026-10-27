/* L08 Q3: Memoise the maximum score to each lattice corner. */
#include <stdio.h>

static int scores[11][11], computed[11][11];
static long long memo[11][11];

static long long best_score(int row, int col) {
    if (computed[row][col]) return memo[row][col];
    long long best = 0;
    if (row == 0 && col > 0) best = best_score(row, col - 1);
    else if (col == 0 && row > 0) best = best_score(row - 1, col);
    else if (row > 0 && col > 0) {
        long long above = best_score(row - 1, col);
        long long left = best_score(row, col - 1);
        best = above > left ? above : left;
    }
    computed[row][col] = 1;
    memo[row][col] = best + scores[row][col];
    return memo[row][col];
}

int main(void) {
    int size;
    if (scanf("%d", &size) != 1 || size < 1 || size > 10) return 1;
    for (int row = 0; row <= size; row++) {
        for (int col = 0; col <= size; col++) {
            if (scanf("%d", &scores[row][col]) != 1) return 1;
        }
    }
    printf("%lld\n", best_score(size, size));
    return 0;
}
