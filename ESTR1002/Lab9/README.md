# Lab9: Dictionaries, dynamic programming and structures

[Course index](../README.md) | [Original exercise](../Description/L09.pdf)

| Source | Exercise | Input | Output |
| --- | --- | --- | --- |
| [Q1.c](Q1.c) | Compact dictionary | Words across any number of lines; bye ends input | Sorted lowercase words with shared prefixes replaced by spaces |
| [Q2.c](Q2.c) | Edit distance | Two lines of at most ten characters each; spaces are significant | Minimum insertion/deletion/substitution count |
| [Q3.c](Q3.c) | Maze reachability | Eleven rows of eleven characters; spaces are passages | 1 if (1,1) can reach (9,9), otherwise 0 |
| [Q4.c](Q4.c) | Containing structure | None; example structure contains i=10 | Value recovered using offsetof |

Dictionary input is case-insensitive, supports multiple lines and dynamically sized words, and stops at the complete word `bye`. Duplicate dictionary entries are printed once. Prefix indentation is relative to the preceding sorted word. Maze input must preserve spaces; do not use whitespace-delimited scanning for its rows.

Build just this lab from the course root:

```sh
cmake -S Lab9 -B build/Lab9
cmake --build build/Lab9
```

For a single target in the full course build: `cmake --build build --target l09_q1`.
