# Lab5: Arrays and linear scans

[Course index](../README.md) | [Original exercise](../Description/L05.pdf)

| Source | Exercise | Input | Output |
| --- | --- | --- | --- |
| [Q1.c](Q1.c) | Binomial coefficient | 0 <= k <= n <= 12 | n choose k |
| [Q2.c](Q2.c) | Increasing matrix | Size from 1 to 10 | Matrix separated by comma and tab |
| [Q3.c](Q3.c) | Equilibrium indices | Length from 3 to 20000, followed by the array | All equilibrium indices or -1 |
| [Q4.c](Q4.c) | Turning-point sum | Length from 1 to 2000, followed by the array | Sum of strict peaks and valleys |
| [Q5.c](Q5.c) | Earliest meeting with Iron Man | Initial X/Y, then route length and directions | Earliest minute or impossible |

Equilibrium indices use running sums in O(n) time. Turning points must be strictly higher or lower than both neighbours, so plateaus do not count. Iron Man can be met at minute zero or at the last route position.

Build just this lab from the course root:

```sh
cmake -S Lab5 -B build/Lab5
cmake --build build/Lab5
```

For a single target in the full course build: `cmake --build build --target l05_q1`.
