# L02: Expressions and number conversion

[Course index](../README.md) | [Original exercise](../Description/L02.pdf)

| Source | Exercise | Input | Output |
| --- | --- | --- | --- |
| [Q1.c](Q1.c) | Inches to centimetres | Integer inches | Centimetres, one decimal place |
| [Q2.c](Q2.c) | Free-fall time | Non-negative tree height in metres | Seconds, two decimal places |
| [Q3.c](Q3.c) | Binary to decimal | Up to four binary digits | Decimal integer |
| [Q4.c](Q4.c) | Decimal to binary | Integer from 0 to 15 | Exactly four binary digits |

Build just this lab from the course root:

```sh
cmake -S L02 -B build/L02
cmake --build build/L02
```

For a single target in the full course build: `cmake --build build --target l02_q1`.
