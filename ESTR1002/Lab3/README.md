# Lab3: Selection and numerical formulas

[Course index](../README.md) | [Original exercise](../Description/L03.pdf)

| Source | Exercise | Input | Output |
| --- | --- | --- | --- |
| [Q1.c](Q1.c) | Giraffe ASCII art | Neck length from 3 to 7 | Giraffe with the requested neck length |
| [Q2.c](Q2.c) | Pay and progressive tax | Monthly work hours from 0 to 500 | Gross pay, tax and net pay |
| [Q3.c](Q3.c) | Train journey duration | Departure and arrival in HHMM format | Minutes from 1 to 1440 |
| [Q4.c](Q4.c) | RGB to HSV | Three RGB components from 0 to 255 | Normalised H, S and V, three decimal places |
| [Q5.c](Q5.c) | Alien numeral base | Decimal value and alien numeral, both from 1 to 999 | Smallest valid base or CHEATED |

Equal departure and arrival times represent a 24-hour journey. An alien digit must be smaller than its base; single-digit numerals still require a base of at least two.

Build just this lab from the course root:

```sh
cmake -S Lab3 -B build/Lab3
cmake --build build/Lab3
```

For a single target in the full course build: `cmake --build build --target l03_q1`.
