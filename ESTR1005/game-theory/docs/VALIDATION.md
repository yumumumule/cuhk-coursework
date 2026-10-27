# Validation record

Validated on **2026-10-28 (Asia/Shanghai)**.

## Local environment

- Windows x64; C11, Zig 0.15.2 / Clang 20.1.2.
- Python 3.14.7, CMake 4.4.4, Ninja.
- Optional oracle: Nashpy 0.0.43, NumPy 2.5.4, SciPy 1.18.1.

Tooling was installed in a temporary virtual environment, outside the source
tree. No generated binaries or environment files are committed.

## Checks completed

| Check | Result |
| --- | --- |
| Direct C11 compilation with `-Wall -Wextra -Wpedantic -Werror` | Passed, no warnings |
| Release build through CMake and Ninja | Passed |
| CTest regression target | Passed |
| 12 Python regression test methods | Passed |
| 300 seeded random integer/continuous games inside the regression suite | Every returned pair passed independent probability, payoff, and deviation checks |
| 150 further seeded continuous random games | Complete equilibrium sets matched the independent oracle |
| Undefined-behavior sanitizer build, with recovery disabled | All 12 regression methods passed |

Regression cases cover pure, mixed, multiple and rectangular equilibria,
single-action players, singular indifference equations, unequal supports,
zero leading pivots, zero matrices, independently scaled payoff matrices,
malformed input, nonfinite numbers, overflow/underflow, oversized tokens,
missing files, invalid arguments, human-readable output, and JSON output.

The oracle uses Nashpy's **polytope vertex enumeration**, rather than repeating
this project's support-enumeration algorithm. One-action cases are checked
analytically. Continuous payoffs avoid intentionally degenerate continua, for
which comparing finite representative lists would not establish completeness.

## Reproduce

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
python -m pip install -r tests/requirements.txt
python tests/cross_check.py build/nash
```

Use the appropriate `.exe` path on Windows. For a direct sanitizer check on
a supporting compiler:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic -Werror \
  -fsanitize=undefined -fno-sanitize-recover=undefined \
  -Iinclude src/main.c src/nash.c -lm -o nash-ubsan
python tests/test_solver.py ./nash-ubsan
```

The course repository also includes a GitHub Actions workflow for Linux,
macOS, and Windows. Remote run status is available on the repository's Actions
page; these local results do not by themselves assert a remote CI outcome.

These checks provide evidence for correctness on the stated examples and
test populations. They do not eliminate floating-point limits in ill-conditioned
games or describe all equilibria in a continuum; see [ALGORITHM.md](ALGORITHM.md).
