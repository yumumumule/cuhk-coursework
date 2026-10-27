# Lab8: Recursion and search

[Course index](../README.md) | [Original exercise](../Description/L08.pdf)

| Source | Exercise | Input | Output |
| --- | --- | --- | --- |
| [Q1.c](Q1.c) | Stair-climbing count | Number of stairs from 1 to 40 | Number of one-step/two-step paths |
| [Q2.c](Q2.c) | Chessboard path count | None | Number of variable-length right/up paths on a 10 by 10 board |
| [Q3.c](Q3.c) | Maximum lattice score | Lattice size from 1 to 10, then an (n+1) by (n+1) score matrix | Maximum score from top left to bottom right |
| [Q4.c](Q4.c) | Row-and-column flip puzzle | Sixteen 0/1 values, in row order | yes if the zero matrix is reachable; otherwise no |

The stair, chessboard and score recursions memoise repeated subproblems. A chess move may span multiple squares. A puzzle move flips the union of the selected row and column, including their intersection exactly once.

Build just this lab from the course root:

```sh
cmake -S Lab8 -B build/Lab8
cmake --build build/Lab8
```

For a single target in the full course build: `cmake --build build --target l08_q1`.
