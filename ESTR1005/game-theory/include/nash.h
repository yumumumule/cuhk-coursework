#ifndef NASH_H
#define NASH_H

#define NASH_MAX_ACTIONS 3
#define NASH_MAX_RESULTS 49
#define NASH_TOLERANCE 1e-8
#define NASH_MAX_PAYOFF 1e100

typedef struct {
    int rows, cols;
    double a[NASH_MAX_ACTIONS][NASH_MAX_ACTIONS];
    double b[NASH_MAX_ACTIONS][NASH_MAX_ACTIONS];
} NashGame;

typedef struct {
    double row[NASH_MAX_ACTIONS], col[NASH_MAX_ACTIONS];
    double row_payoff, col_payoff;
    double row_regret, col_regret;
    double row_relative_regret, col_relative_regret;
    int pure;
} NashEquilibrium;

typedef struct {
    int count, support_pairs_checked;
    NashEquilibrium equilibria[NASH_MAX_RESULTS];
} NashResult;

/* Returns 0 on success, -1 for invalid input, -2 for numerical failure.
 * Returns distinct representatives, not a parameterization of continua.
 * Both players maximize their own payoff matrix. */
int nash_solve(const NashGame *game, NashResult *result);

#endif
