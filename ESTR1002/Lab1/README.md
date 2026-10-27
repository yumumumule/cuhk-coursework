# Lab1: Output and arithmetic

[Course index](../README.md) | [Original exercise](description.pdf)

| Source | Exercise | Input | Output |
| --- | --- | --- | --- |
| [Q1.c](Q1.c) | Welcome message | None | Two lines of text |
| [Q2.c](Q2.c) | Sphere surface area and volume | Radius as a floating-point number | Area and volume, four decimal places |
| [Q3.c](Q3.c) | Whale ASCII art | None | Six lines of escaped characters |

Build just this lab from the course root:

```sh
cmake -S Lab1 -B build/Lab1
cmake --build build/Lab1
```

For a single target in the full course build: `cmake --build build --target l01_q1`.
