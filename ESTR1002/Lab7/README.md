# Lab7: Text decoding and numerical methods

[Course index](../README.md) | [Original exercise](description.pdf)

| Source | Exercise | Input | Output |
| --- | --- | --- | --- |
| [Q1.c](Q1.c) | Hidden message | Paragraph of at most 200 characters, then one line of one-based indices | Selected characters in lowercase |
| [Q2.c](Q2.c) | UTF-8 output | None | The character 日 followed by A on the next line |
| [Q3.c](Q3.c) | Monte Carlo estimate of pi | None | Estimate from 100000000 samples |
| [Q4.c](Q4.c) | Cubic equation roots | Coefficients a b c d | Approximate real or complex roots, one per line |

`Q1` indices count every character, including spaces and punctuation. `Q2` writes UTF-8 bytes; use a UTF-8 terminal (for older Windows consoles, run `chcp 65001`). `Q3` uses a fixed random seed for repeatable runs on the same C runtime; its estimate is statistical. `Q4` uses at most 512 safeguarded Newton iterations, then polynomial division and a quadratic solver. Roots are printed to six decimal places, without a prescribed order, and repeated roots are retained. If a=0, it handles quadratic, linear and constant equations. Constant equations print `No solution` or `Infinitely many solutions`. Very ill-conditioned coefficients remain subject to floating-point error.

Build just this lab from the course root:

```sh
cmake -S Lab7 -B build/Lab7
cmake --build build/Lab7
```

For a single target in the full course build: `cmake --build build --target l07_q1`.
