# Lab4: Loops and text patterns

[Course index](../README.md) | [Original exercise](description.pdf)

| Source | Exercise | Input | Output |
| --- | --- | --- | --- |
| [Q1.c](Q1.c) | Count digit 1 | Non-negative integer at most 5000000 | Number of occurrences |
| [Q2.c](Q2.c) | Decreasing triangle | Size from 1 to 15 | Comma-separated rows |
| [Q3.c](Q3.c) | Monthly calendar | First weekday (Sunday=0) and 28 to 31 days | Aligned calendar |
| [Q4.c](Q4.c) | Star pattern | Positive odd size | Pattern using lowercase x and dots |
| [Q5.c](Q5.c) | Capital A pattern | Positive odd size | Pattern using asterisks and dots |
| [Q6.c](Q6.c) | Special rows and columns | Size from 1 to 100 | Pattern using ., # and @ |

Build just this lab from the course root:

```sh
cmake -S Lab4 -B build/Lab4
cmake --build build/Lab4
```

For a single target in the full course build: `cmake --build build --target l04_q1`.
