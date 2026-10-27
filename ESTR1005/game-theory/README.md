# Bimatrix Nash Solver

A small C11 project for CUHK ESTR1005: compute pure and mixed Nash equilibria
in two-player normal-form games with **1–3 actions per player**.

[中文说明](README.zh-CN.md) · [Algorithm and limitations](docs/ALGORITHM.md) ·
[Validation record](docs/VALIDATION.md)

Both players maximize their own payoffs: `A[i][j]` belongs to the row player,
and `B[i][j]` belongs to the column player. Zero-sum games are the special case
`B = -A`; the solver also handles general-sum games such as coordination games.

## Build and run

Requires a C11 compiler. From this project directory, on Linux/macOS:

```sh
cc -std=c11 -O2 -Wall -Wextra -Wpedantic -Iinclude src/main.c src/nash.c -lm -o nash
./nash --file examples/battle_of_the_sexes.txt
```

On Windows with MinGW-w64, use `gcc` and `-o nash.exe`, then run
`.\nash.exe --file examples/battle_of_the_sexes.txt` in PowerShell.
With a portable Zig installation, `zig cc` can replace `cc` in the command.
The executable requires no Python packages or external solver libraries.

Or use CMake 3.16+, an available C toolchain and Python 3.8+ for tests:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

The executable is `build/nash` on typical Unix builds, `build/nash.exe` with
Ninja/MinGW on Windows, or `build/Release/nash.exe` with Visual Studio.
For a build without tests or Python, configure with `-DBUILD_TESTING=OFF`.

On Windows with Zig and Ninja, set `$env:ZIG_EXE` to the full path of `zig.exe`
and configure with `-G Ninja` and
`"-DCMAKE_C_COMPILER=$((Resolve-Path scripts/zig-cc.cmd).Path)"`.
The wrapper forwards CMake's compiler invocations to `zig cc`.

## Input

First supply `rows cols`. Then supply all of matrix A, followed by all of
matrix B, in row order. Dimensions range from 1 to 3. Whitespace and `#` comments
are accepted. Payoffs must be finite with absolute value at most `1e100`;
numbers that overflow or underflow `strtod` are rejected.

```text
2 2
# A: row player; actions Opera, Football
2 0
0 1
# B: column player; same action order
1 0
0 2
```

```sh
./nash --file examples/battle_of_the_sexes.txt
./nash --file examples/rock_paper_scissors.txt --json
./nash --zero-sum --file examples/zero_sum_legacy.txt
./nash --help
```

Without `--file`, input is read from standard input. `--zero-sum` reads only A
and derives B. To adapt the original nine-number program's input, prepend
`3 3` and pass `--zero-sum`. Plain nine-number input is no longer the default,
because a general bimatrix game needs both payoff matrices.

## Reading the results

Each result contains both probability vectors, both expected payoffs, and each
player's maximum gain from changing strategy alone. A Nash equilibrium makes
those gains zero, within the documented numerical tolerance. Action positions
follow the input order. Human-readable probabilities use six decimals; JSON
retains double precision for further analysis.

For the coordination example above, the three equilibria are:

| Type | Row strategy | Column strategy | Expected payoffs (row, column) |
| --- | --- | --- | --- |
| Pure | `(1, 0)` | `(1, 0)` | `(2, 1)` |
| Pure | `(0, 1)` | `(0, 1)` | `(1, 2)` |
| Mixed | `(2/3, 1/3)` | `(1/3, 2/3)` | `(2/3, 2/3)` |

`--json` writes one object with `rows`, `cols`, `support_pairs_checked`,
`normalized_tolerance`, `enumeration`, and `equilibria`. Each equilibrium has
`type`, `row_strategy`, `column_strategy`, the two `*_payoff` fields, raw
`*_regret` fields, and `*_normalized_regret` fields.

**Scope:** results are distinct equilibrium representatives. In nondegenerate,
well-conditioned games this enumerates isolated equilibria. Degenerate games
can have infinitely many equilibria; this implementation selects one feasible
strategy pair per support pair and does not describe an entire continuum.
Candidates within `1e-7` per probability coordinate are deduplicated.

Exit status is `0` for success, `1` for invalid input/arguments, and `2` if no
numerically verified candidate was found. Status 2 is a numerical limitation;
it is not a proof that the finite game has no Nash equilibrium.

## Examples and testing

| Example | Purpose |
| --- | --- |
| `battle_of_the_sexes.txt` | General-sum game with two pure and one mixed equilibrium |
| `prisoners_dilemma.txt` | Dominant strategies; unique mutual-defection equilibrium |
| `rock_paper_scissors.txt` | Fully mixed 3×3 equilibrium; zero leading elimination pivot |
| `matching_pennies.txt` | Mixed 2×2 equilibrium |
| `rectangular.txt` | A 2×3 general-sum game |
| `degenerate.txt` | Singular indifference equations and a continuum of equilibria |
| `zero_sum_legacy.txt` | Single-matrix compatibility mode with dimensions |

```sh
python tests/test_solver.py build/nash
# Optional independent oracle comparison:
python -m pip install -r tests/requirements.txt
python tests/cross_check.py build/nash
```

Use the Windows executable path as appropriate. The regression suite requires
only the Python standard library. Optional Nashpy comparison checks the full
equilibrium sets of 150 seeded continuous random games; the regression suite
also checks 300 random games directly against best-response inequalities.

## Project structure

```text
include/nash.h         Reusable game/result structures and solver API
src/nash.c             Support enumeration and active-constraint feasibility
src/main.c             Validated input, text output and JSON output
examples/              Small games suitable for demonstration
tests/                 Regression suite and independent oracle comparison
docs/                  Mathematical explanation and validation record
scripts/zig-cc.cmd     Optional Windows Zig compiler wrapper
CMakeLists.txt         Portable build and CTest integration
```

This is an educational implementation using double-precision arithmetic,
intended for small course examples. The [algorithm notes](docs/ALGORITHM.md)
explain the assumptions, improvements over the starting code, and numerical
limits. No assignment handouts, account credentials, or generated build files
are included.
