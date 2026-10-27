# Source review and validation

All 46 exercises were checked against the ten original handouts. The review
covered required input/output, algorithm behaviour, comments, initialisation,
array boundaries, allocation and release, function signatures, and build files.
Comments describe the exercise or explain a non-obvious choice; they do not
repeat every C statement. Sources use UTF-8 and four-space indentation.

## Corrections

| Lab | Review result and corrections |
| --- | --- |
| L01 | Standardised main signatures and output spacing; retained the welcome message, sphere formulas and whale drawing. |
| L02 | Recovered all four sources from the submission ZIP; fixed malformed scanf formats and clarified binary digit extraction. |
| L03 | Retained the giraffe cases and progressive pay calculation. Calculated journey duration in minutes, including midnight and equal times. Simplified HSV maximum/minimum selection. Required integral alien bases larger than every digit and verified them by exact substitution. |
| L04 | Initialised the digit counter; kept calendar alignment and completed final newlines. Matched the handout's lowercase x star. Clarified A-pattern conditions and triangular-number columns. |
| L05 | Handled 0! correctly. Preserved comma/tab matrix formatting. Removed the equilibrium scan's read past the array and used wide sums. Handled short arrays and plateaus in turning-point sums. Checked meeting times without reading a nonexistent final route move. |
| L06 | Fixed OR-versus-AND character-range checks and bounded password storage. Allowed the full 2000-character compression input. Replaced uninitialised/cancelling anagram sums with per-letter counts. Normalised vowel rotations. Replaced the uninitialised alien digit mapping with a minimum-base, 64-bit calculation. |
| L07 | Terminated paragraph input correctly and read one line of indices. Wrote the Chinese character as UTF-8 bytes. Corrected the Monte Carlo denominator. Bounded Newton iteration, guarded zero derivatives, and handled quadratic, linear, constant and complex-root cases. |
| L08 | Memoised repeated recursive states for stairs, chessboard paths and lattice scores; used wide counts/sums. Preserved exhaustive flip search and flipped row/column intersections once. |
| L09 | Rebuilt dictionary parsing for multi-line input, case folding, complete words, dynamic storage, sorting and prefix indentation. Read full ten-character edit-distance inputs and removed line endings only. Preserved maze spaces. Used offsetof instead of a fixed structure offset. |
| L10 | Printed just the username value and supported USER as a fallback. Allocated all three name lists according to the input count, checked allocations and freed memory. Fixed the flexible-array structure pointer passed to foo. Moved Q3 into L10, added a guarded shared header/prototype, and scanned the last array element. |

All obsolete CMake references to missing main.c files were replaced by explicit
targets for the actual sources. Labs can be built together or individually.
Submission ZIPs, executables, debug symbols, generated CMake directories and stale
IDE state are absent from the upload. The local Project directory is ignored.

## Verification

- Compiled all 46 exercise programs with MinGW-w64 GCC 13.1.0 in C11 mode and
  `-Wall -Wextra -Wpedantic`; no warnings.
- Passed all 462 checks in `tests/regression.py`, also through CTest.
- Ran the full-size 100000000-sample Monte Carlo estimate and the
  100000000-element maximum program.
- Tested the actual maximum function separately with the maximum at the first
  and last positions, all-negative data, and repeated values.
- Compared generated cases against independent Python references for colour
  conversion, numeral bases, equilibrium indices and other discrete exercises.
- Checked the handout's visual examples for the whale, giraffe, patterns and
  dictionary indentation.

The regression suite uses only the Python standard library. Monte Carlo output
is checked with a statistical tolerance. Numerical roots are approximate and
checked with a floating-point tolerance; extreme ill-conditioned coefficients
can still lose precision. Linux, macOS and MSVC execution have not been tested.
The envp parameter in L10 Q1 is deliberately retained as required by the lab.
