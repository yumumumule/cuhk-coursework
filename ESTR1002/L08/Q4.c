/* L08 Q4: Search subsets of the 16 possible row-and-column flips. */
#include <stdio.h>

static void flip(int position, int cells[16]) {
    for (int i = 0; i < 16; i++) {
        /* The intersection belongs to the union and is flipped once. */
        if (i / 4 == position / 4 || i % 4 == position % 4) cells[i] = !cells[i];
    }
}

static int is_zero(const int cells[16]) {
    for (int i = 0; i < 16; i++) {
        if (cells[i] != 0) return 0;
    }
    return 1;
}

static int attempt(int position, int cells[16]) {
    if (is_zero(cells)) return 1;
    if (position == 16) return 0;
    /* Flips commute and doing the same flip twice cancels it. */
    if (attempt(position + 1, cells)) return 1;
    flip(position, cells);
    int solved = attempt(position + 1, cells);
    flip(position, cells);
    return solved;
}

int main(void) {
    int cells[16];
    for (int i = 0; i < 16; i++) {
        if (scanf("%d", &cells[i]) != 1 || (cells[i] != 0 && cells[i] != 1)) return 1;
    }
    puts(attempt(0, cells) ? "yes" : "no");
    return 0;
}
