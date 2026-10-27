#include "nash.h"
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void usage(void) {
    puts("Bimatrix Nash Solver - ESTR1005\n"
         "Usage: nash [--file PATH] [--json] [--zero-sum]\n"
         "       nash --help\n\n"
         "Default input: rows cols, then A, then B (both players maximize).\n"
         "Each dimension must be 1..3; matrix entries are in row-major order.\n"
         "With --zero-sum: read only A and set B = -A.\n"
         "Whitespace and # comments are allowed. Input defaults to stdin.\n"
         "Returns distinct equilibrium representatives, not entire continua.\n"
         "Exit codes: 0 success; 1 invalid arguments/input; 2 numerical failure.");
}

/* Read a bounded token. Reject oversized tokens rather than splitting them. */
static int token(FILE *in, char out[128]) {
    int c, length = 0, overflow = 0;
    for (;;) {
        c = fgetc(in);
        if (c == '#') { while (c != '\n' && c != EOF) c = fgetc(in); }
        if (c == EOF) return ferror(in) ? -1 : 0;
        if (c != ' ' && c != '\n' && c != '\r' && c != '\t' && c != '\v' && c != '\f') break;
    }
    do {
        if (length < 127) out[length++] = (char)c;
        else overflow = 1;
        c = fgetc(in);
    } while (c != EOF && c != '#' && c != ' ' && c != '\n' && c != '\r' &&
             c != '\t' && c != '\v' && c != '\f');
    if (c == '#') { while (c != '\n' && c != EOF) c = fgetc(in); }
    out[length] = '\0';
    return overflow || ferror(in) ? -1 : 1;
}

static int dimension(FILE *in, int *value) {
    char text[128], *end;
    if (token(in, text) != 1) return 0;
    errno = 0;
    long parsed = strtol(text, &end, 10);
    if (errno || *end || parsed < 1 || parsed > NASH_MAX_ACTIONS) return 0;
    *value = (int)parsed;
    return 1;
}

static int matrix(FILE *in, double data[3][3], int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            char text[128], *end;
            if (token(in, text) != 1) return 0;
            errno = 0;
            double value = strtod(text, &end);
            if (errno || *end || !isfinite(value) || fabs(value) > NASH_MAX_PAYOFF) return 0;
            data[i][j] = value;
        }
    }
    return 1;
}

static void vector(const double *values, int n, int json) {
    putchar('[');
    for (int i = 0; i < n; ++i) {
        if (i) printf(json ? "," : ", ");
        printf(json ? "%.17g" : "%.6f", values[i]);
    }
    putchar(']');
}

static void print_result(const NashGame *g, const NashResult *r, int json) {
    if (json) {
        printf("{\"rows\":%d,\"cols\":%d,\"support_pairs_checked\":%d,"
               "\"normalized_tolerance\":%.17g,\"enumeration\":\"representatives\",\"equilibria\":[",
               g->rows, g->cols, r->support_pairs_checked, NASH_TOLERANCE);
    } else {
        printf("Bimatrix Nash Solver | %d x %d game\n", g->rows, g->cols);
        printf("Checked %d support pairs; found %d distinct representative(s).\n",
               r->support_pairs_checked, r->count);
        puts("Both players maximize their own payoffs. Actions are ordered as in the input.");
    }
    for (int k = 0; k < r->count; ++k) {
        const NashEquilibrium *e = &r->equilibria[k];
        if (json) {
            if (k) putchar(',');
            printf("{\"type\":\"%s\",\"row_strategy\":", e->pure ? "pure" : "mixed");
            vector(e->row, g->rows, 1);
            printf(",\"column_strategy\":"); vector(e->col, g->cols, 1);
            printf(",\"row_payoff\":%.17g,\"column_payoff\":%.17g,"
                   "\"row_regret\":%.17g,\"column_regret\":%.17g,"
                   "\"row_normalized_regret\":%.17g,\"column_normalized_regret\":%.17g}",
                   e->row_payoff, e->col_payoff, e->row_regret, e->col_regret,
                   e->row_relative_regret, e->col_relative_regret);
        } else {
            printf("\nEquilibrium %d (%s)\n  Row strategy:    ", k + 1, e->pure ? "pure" : "mixed");
            vector(e->row, g->rows, 0);
            printf("\n  Column strategy: "); vector(e->col, g->cols, 0);
            printf("\n  Expected payoffs: row = %.9g, column = %.9g\n", e->row_payoff, e->col_payoff);
            printf("  Unilateral gain: row = %.3g, column = %.3g\n", e->row_regret, e->col_regret);
            printf("  Normalized gain: row = %.3g, column = %.3g\n",
                   e->row_relative_regret, e->col_relative_regret);
        }
    }
    if (json) puts("]}");
    else puts("\nDegenerate games can have infinitely many equilibria; this lists representatives.\n"
              "Acceptance tolerance: 1e-8 after scaling each payoff matrix by its largest absolute entry.");
}

int main(int argc, char **argv) {
    const char *path = NULL;
    int json = 0, zero_sum = 0;
    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")) { usage(); return 0; }
        if (!strcmp(argv[i], "--json") && !json) json = 1;
        else if (!strcmp(argv[i], "--zero-sum") && !zero_sum) zero_sum = 1;
        else if (!strcmp(argv[i], "--file") && !path && i + 1 < argc) path = argv[++i];
        else { fprintf(stderr, "Invalid or repeated option: %s (see --help)\n", argv[i]); return 1; }
    }
    FILE *in = path ? fopen(path, "r") : stdin;
    if (!in) { fprintf(stderr, "Cannot open input: %s\n", path); return 1; }
    NashGame g = {0};
    int valid = dimension(in, &g.rows) && dimension(in, &g.cols);
    if (valid) valid = matrix(in, g.a, g.rows, g.cols);
    if (valid && !zero_sum) valid = matrix(in, g.b, g.rows, g.cols);
    if (valid && zero_sum)
        for (int i = 0; i < g.rows; ++i)
            for (int j = 0; j < g.cols; ++j) g.b[i][j] = -g.a[i][j];
    char extra[128];
    if (valid) valid = token(in, extra) == 0;
    if (path) fclose(in);
    if (!valid) {
        fputs("Invalid input. Expected dimensions (1..3), then finite A and B matrices\n"
              "with |payoff| <= 1e100; --zero-sum reads A only. No extra tokens allowed.\n", stderr);
        return 1;
    }
    NashResult result;
    int status = nash_solve(&g, &result);
    if (status) {
        fputs("No numerically verified equilibrium found. Check payoff conditioning.\n", stderr);
        return 2;
    }
    print_result(&g, &result, json);
    return 0;
}
