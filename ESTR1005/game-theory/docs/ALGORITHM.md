# Model and algorithm

## Bimatrix model

Let `A, B` be real `m × n` payoff matrices, with `1 <= m,n <= 3`.
The row player chooses a probability vector `x`; the column player chooses `y`.
Expected utilities are `u = x^T A y` and `v = x^T B y`.
Both players maximize their own utility.

A Nash equilibrium is a pair of mutual best responses. The row player's pure
action payoffs are `(Ay)_i`; the column player's are `(x^T B)_j`. Every action
played with positive probability must attain that player's largest action payoff.

## Enumerating supports

For each nonempty row support `I` and column support `J`, construct two separate
feasibility problems. For the column distribution, choose a reference row `r` in I:

```text
sum_{j in J} y_j = 1
y_j >= 0                                    for j in J
sum_{j in J} (A_ij - A_rj) y_j = 0           for i in I other than r
sum_{j in J} (A_kj - A_rj) y_j <= 0          for k outside I
y_j = 0                                     for j outside J
```

The row distribution is obtained by applying the same construction to `B^T`
with supports `(J, I)`. With supports fixed, these problems are independent:
any feasible x and y satisfy the corresponding best-response conditions.

Zero coordinates are allowed within a candidate support. Such a point is an
equilibrium with a smaller actual support and is deduplicated later.
Supports of unequal sizes are included, which matters in degenerate games.

## Finding a feasible point

The constraints define a closed bounded polytope inside a probability simplex.
A nonempty bounded polytope has a vertex. At a vertex, enough independent
constraints are active to determine every free probability coordinate.

With `s = |J|` variables, enumerate subsets of `s` constraints, treat those as
equalities, solve using Gaussian elimination with partial pivoting, and check
the candidate against **all** original equalities and inequalities. Singular
subsets are skipped; redundant equalities do not force a divide by zero.
Normalize each nonzero difference constraint by its largest absolute coefficient.

For each support pair, the implementation keeps the first feasible y and x,
then recomputes both best-response gains before accepting the pair. It removes
duplicate pairs using an absolute probability tolerance of `1e-7`.

For a 3×3 game there are `(2^3 - 1)^2 = 49` support pairs. Each feasibility
problem has at most 3 variables and 6 constraints, requiring at most
`C(6, 3) = 20` small linear solves. The fixed arrays are deliberately bounded
for a small educational program, rather than a large-game optimization library.

## Validation and floating-point limits

For each player, divide their payoff matrix by its maximum absolute entry
(use 1 when all entries are zero). This positive scaling preserves preferences.
The final check evaluates:

```text
row gain    = max_i (Ay)_i - x^T A y
column gain = max_j (x^T B)_j - x^T B y
```

These are the best possible unilateral gains: a linear expected payoff over
the simplex attains a maximum at a pure action. Checking pure deviations is
therefore enough to check deviations to any mixed strategy.

Normalized gains must be at most `1e-8`. Values infinitesimally below zero due
to rounding are clamped to zero. The output also reports gains in original
payoff units. The elimination pivot threshold is `1e-12` after row scaling.
Tiny negative probabilities within the constraint tolerance are clamped and
renormalized, followed by another feasibility check and final gain checks.

This is an approximate floating-point solver, not an exact arithmetic proof.
Near-singular games, extreme dynamic ranges within one matrix, and equilibria
closer than the deduplication tolerance can lose information. Finite payoff
entries are restricted to magnitude `1e100` to leave arithmetic headroom.

## What the result list means

For nondegenerate games with well-separated, well-conditioned solutions,
support enumeration recovers all isolated equilibria. For degenerate games,
the feasible sets may have positive dimension and contain infinitely many
equilibria. This solver returns at most one candidate per support pair, not
all vertices or a symbolic parameterization of those sets. Even an all-zero
3×3 game has infinitely many mixed equilibria; the demo returns nine pure
representatives. Its output is intentionally labeled `representatives`.

Nash's existence theorem guarantees an equilibrium for every finite game.
If numerical checks find none, the program reports numerical failure instead
of the original, misleading `no solution` message.

## Changes from the starting program

| Starting behavior | Revised behavior |
| --- | --- |
| Reads only A | Reads both payoff matrices; explicit zero-sum shortcut |
| Assumes all three row actions are indifferent | Enumerates all possible supports for both players |
| Divides by a diagonal entry without pivoting | Partial pivoting and singular-system detection |
| Reuses row-pair indices as column support indices | Separate row and column support masks |
| Uses `-c/(a-b)` for an unrelated two-column mixture | Solves the actual supported indifference constraints |
| Checks only one player's outside action | Checks every pure deviation for each player |
| Checks negative probabilities but not NaN | Rejects nonfinite input and intermediate solutions |
| Prints one vector | Prints both strategies, payoffs and deviation gains |
| Prints `no solution` | Distinguishes invalid input from numerical failure |

For a specified pair of columns s,t and rows i,k, the correct single
indifference equation is `d_s p + d_t (1-p) = 0`, where
`d_j = A_ij - A_kj`. Thus `p = -d_t / (d_s - d_t)` when the denominator is
nonzero. This only checks those two rows; it is insufficient by itself to
establish a general bimatrix equilibrium.

## References

- [Nashpy: support enumeration](https://nashpy.readthedocs.io/en/stable/text-book/support-enumeration.html)
  develops the best-response equations for two-player games; the rectangular
  example in this project comes from its exercise.
- [Daskalakis and Farina: centralized algorithms for Nash equilibrium computation,
  MIT 6.7980](https://www.mit.edu/~6.7980/nash_algorithms.html)
  gives the support-based feasibility formulation and discusses computational
  complexity for general games.

The project extends the basic equal-sized-support equation method with bounded
polytope feasibility to produce representatives for degenerate games.
