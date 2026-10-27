# Lab6: Strings and character processing

[Course index](../README.md) | [Original exercise](../Description/L06.pdf)

| Source | Exercise | Input | Output |
| --- | --- | --- | --- |
| [Q1.c](Q1.c) | Password strength | Password of length 6 to 30 | yes or no |
| [Q2.c](Q2.c) | Run-length encoding | At most 2000 non-digit characters | Character runs with repeated counts |
| [Q3.c](Q3.c) | Case-insensitive anagrams | Two lines, each at most 1000 characters | yes or no; spaces are ignored |
| [Q4.c](Q4.c) | Circular vowel shift | Letter string of at most 200 characters and integer K | String with vowels rotated |
| [Q5.c](Q5.c) | Minimum alien numeral value | Symbol string of length 1 to 60 | Smallest possible positive integer value |

Password punctuation follows the exact list in the exercise. Positive K rotates vowels left; negative K rotates them right. A vowel retains its own case. Alien numerals assign 1 to the first symbol, 0 to the next distinct symbol, then 2, 3, and so on; the base is at least two.

Build just this lab from the course root:

```sh
cmake -S Lab6 -B build/Lab6
cmake --build build/Lab6
```

For a single target in the full course build: `cmake --build build --target l06_q1`.
