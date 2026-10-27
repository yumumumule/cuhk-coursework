/* L09 Q3: Depth-first search through spaces in an 11-by-11 maze. */
#include <stdio.h>
#include <string.h>

static char maze[11][11];
static int visited[11][11];

static int reachable(int row, int col) {
    if (row < 0 || row >= 11 || col < 0 || col >= 11 ||
        maze[row][col] != ' ' || visited[row][col]) return 0;
    if (row == 9 && col == 9) return 1;
    visited[row][col] = 1;
    return reachable(row + 1, col) || reachable(row - 1, col) ||
           reachable(row, col + 1) || reachable(row, col - 1);
}

int main(void) {
    for (int row = 0; row < 11; row++) {
        char line[14];
        if (fgets(line, sizeof(line), stdin) == NULL) return 1;
        if (strcspn(line, "\r\n") != 11) return 1;
        memcpy(maze[row], line, 11);
    }
    printf("%d\n", reachable(1, 1));
    return 0;
}
