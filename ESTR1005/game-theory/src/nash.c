#include "nash.h"
#include <math.h>
#include <string.h>

#define MAX_CONSTRAINTS (2 * NASH_MAX_ACTIONS)
#define PIVOT_TOL 1e-12
#define DUPLICATE_TOL 1e-7

typedef struct {
    double a[MAX_CONSTRAINTS][NASH_MAX_ACTIONS];
    double b[MAX_CONSTRAINTS];
    int equality[MAX_CONSTRAINTS];
    int count, variables;
} Polytope;

static int bits(unsigned mask) {
    int n = 0;
    while (mask) { n += (int)(mask & 1u); mask >>= 1; }
    return n;
}

/* Gaussian elimination with partial pivoting. Singular active sets are skipped. */
static int linear_solve(double a[3][3], double b[3], int n, double x[3]) {
    for (int k = 0; k < n; ++k) {
        int pivot = k;
        for (int i = k + 1; i < n; ++i)
            if (fabs(a[i][k]) > fabs(a[pivot][k])) pivot = i;
        if (fabs(a[pivot][k]) < PIVOT_TOL) return 0;
        if (pivot != k) {
            for (int j = 0; j < n; ++j) {
                double t = a[k][j]; a[k][j] = a[pivot][j]; a[pivot][j] = t;
            }
            double t = b[k]; b[k] = b[pivot]; b[pivot] = t;
        }
        for (int i = k + 1; i < n; ++i) {
            double factor = a[i][k] / a[k][k];
            for (int j = k; j < n; ++j) a[i][j] -= factor * a[k][j];
            b[i] -= factor * b[k];
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        double value = b[i];
        for (int j = i + 1; j < n; ++j) value -= a[i][j] * x[j];
        x[i] = value / a[i][i];
        if (!isfinite(x[i])) return 0;
    }
    return 1;
}

static int feasible(const Polytope *p, const double x[3]) {
    for (int i = 0; i < p->count; ++i) {
        double residual = -p->b[i];
        for (int j = 0; j < p->variables; ++j) residual += p->a[i][j] * x[j];
        if (p->equality[i] ? fabs(residual) > NASH_TOLERANCE
                           : residual > NASH_TOLERANCE) return 0;
    }
    return 1;
}

/* Find an opponent distribution making every action in own_mask a best
 * response. Enumerating active constraints handles unequal supports and
 * redundant indifference equations without dividing by zero. */
static int distribution(double payoff[3][3], int actions, int opponent_actions,
                        unsigned own_mask, unsigned opponent_mask, double out[3]) {
    Polytope p = {0};
    int index[3], reference = 0;
    for (int j = 0; j < opponent_actions; ++j)
        if (opponent_mask & (1u << j)) index[p.variables++] = j;
    while (!(own_mask & (1u << reference))) ++reference;
    p.equality[0] = 1;
    p.b[0] = 1;
    for (int j = 0; j < p.variables; ++j) p.a[0][j] = 1;
    p.count = 1;
    for (int i = 0; i < actions; ++i) {
        if (i == reference) continue;
        int r = p.count++;
        double scale = 0;
        p.equality[r] = (own_mask & (1u << i)) != 0;
        for (int j = 0; j < p.variables; ++j) {
            p.a[r][j] = payoff[i][index[j]] - payoff[reference][index[j]];
            scale = fmax(scale, fabs(p.a[r][j]));
        }
        if (scale > 0)
            for (int j = 0; j < p.variables; ++j) p.a[r][j] /= scale;
    }
    for (int j = 0; j < p.variables; ++j) p.a[p.count++][j] = -1;

    /* A nonempty bounded polytope has a vertex. A vertex has enough linearly
     * independent active constraints to solve for all its variables. */
    for (unsigned active = 1; active < (1u << p.count); ++active) {
        if (bits(active) != p.variables) continue;
        double a[3][3] = {{0}}, b[3] = {0}, x[3] = {0};
        int row = 0;
        for (int r = 0; r < p.count; ++r) {
            if (!(active & (1u << r))) continue;
            for (int j = 0; j < p.variables; ++j) a[row][j] = p.a[r][j];
            b[row++] = p.b[r];
        }
        if (!linear_solve(a, b, p.variables, x) || !feasible(&p, x)) continue;
        double sum = 0;
        for (int j = 0; j < p.variables; ++j) {
            x[j] = fmax(0, x[j]);
            sum += x[j];
        }
        if (sum <= 0) continue;
        for (int j = 0; j < p.variables; ++j) x[j] /= sum;
        if (!feasible(&p, x)) continue;
        memset(out, 0, 3 * sizeof(double));
        for (int j = 0; j < p.variables; ++j) out[index[j]] = x[j];
        return 1;
    }
    return 0;
}

static int same(const NashEquilibrium *a, const NashEquilibrium *b, int m, int n) {
    for (int i = 0; i < m; ++i)
        if (fabs(a->row[i] - b->row[i]) > DUPLICATE_TOL) return 0;
    for (int j = 0; j < n; ++j)
        if (fabs(a->col[j] - b->col[j]) > DUPLICATE_TOL) return 0;
    return 1;
}

int nash_solve(const NashGame *g, NashResult *result) {
    if (!g || !result) return -1;
    memset(result, 0, sizeof(*result));
    if (g->rows < 1 || g->rows > 3 || g->cols < 1 || g->cols > 3) return -1;
    double a[3][3] = {{0}}, bt[3][3] = {{0}}, scale_a = 0, scale_b = 0;
    for (int i = 0; i < g->rows; ++i) {
        for (int j = 0; j < g->cols; ++j) {
            if (!isfinite(g->a[i][j]) || !isfinite(g->b[i][j]) ||
                fabs(g->a[i][j]) > NASH_MAX_PAYOFF || fabs(g->b[i][j]) > NASH_MAX_PAYOFF)
                return -1;
            scale_a = fmax(scale_a, fabs(g->a[i][j]));
            scale_b = fmax(scale_b, fabs(g->b[i][j]));
        }
    }
    if (scale_a == 0) scale_a = 1;
    if (scale_b == 0) scale_b = 1;
    for (int i = 0; i < g->rows; ++i)
        for (int j = 0; j < g->cols; ++j) {
            a[i][j] = g->a[i][j] / scale_a;
            bt[j][i] = g->b[i][j] / scale_b;
        }
    for (unsigned im = 1; im < (1u << g->rows); ++im) {
        for (unsigned jm = 1; jm < (1u << g->cols); ++jm) {
            ++result->support_pairs_checked;
            NashEquilibrium e = {0};
            if (!distribution(a, g->rows, g->cols, im, jm, e.col) ||
                !distribution(bt, g->cols, g->rows, jm, im, e.row)) continue;
            double row_values[3] = {0}, col_values[3] = {0};
            double u = 0, v = 0, best_row = -INFINITY, best_col = -INFINITY;
            int row_support = 0, col_support = 0;
            for (int i = 0; i < g->rows; ++i) {
                for (int j = 0; j < g->cols; ++j) row_values[i] += a[i][j] * e.col[j];
                u += e.row[i] * row_values[i];
                best_row = fmax(best_row, row_values[i]);
                row_support += e.row[i] > NASH_TOLERANCE;
            }
            for (int j = 0; j < g->cols; ++j) {
                for (int i = 0; i < g->rows; ++i) col_values[j] += bt[j][i] * e.row[i];
                v += e.col[j] * col_values[j];
                best_col = fmax(best_col, col_values[j]);
                col_support += e.col[j] > NASH_TOLERANCE;
            }
            e.row_relative_regret = fmax(0, best_row - u);
            e.col_relative_regret = fmax(0, best_col - v);
            if (e.row_relative_regret > NASH_TOLERANCE ||
                e.col_relative_regret > NASH_TOLERANCE) continue;
            e.row_payoff = u * scale_a;
            e.col_payoff = v * scale_b;
            e.row_regret = e.row_relative_regret * scale_a;
            e.col_regret = e.col_relative_regret * scale_b;
            e.pure = row_support == 1 && col_support == 1;
            int duplicate = 0;
            for (int k = 0; k < result->count; ++k)
                if (same(&e, &result->equilibria[k], g->rows, g->cols)) duplicate = 1;
            if (!duplicate) result->equilibria[result->count++] = e;
        }
    }
    return result->count ? 0 : -2;
}
