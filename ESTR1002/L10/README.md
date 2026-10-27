# L10: Pointers, arrays and allocation

[Course index](../README.md) | [Original exercise](../Description/L10.pdf)

| Source | Exercise | Input | Output |
| --- | --- | --- | --- |
| [Q1_task1.c](Q1_task1.c) | Print the environment | Process environment | All environment strings, using pointer traversal |
| [Q1_task2.c](Q1_task2.c) | Extract the login name | USERNAME, falling back to USER | The username value only |
| [Q2_task1.c](Q2_task1.c) | Reverse names through char ** | Student count, then one name per line | Names in reverse order |
| [Q2_task2.c](Q2_task2.c) | Reverse names through a structure pointer | Student count, then one name per line | Names in reverse order |
| [Q2_task3.c](Q2_task3.c) | Reverse names through a flexible array | Student count, then one name per line | Names in reverse order |
| [Q3/](Q3/) | Maximum of a large array | None; main generates random integers | Maximum of all 100000000 elements |

`Q1` deliberately uses the third `main` parameter (`envp`) from the handout; this is a supported implementation extension on common Windows and Unix C toolchains, rather than an ISO C signature. No actual environment values are stored in this repository. Each student name is at most 14 characters and may contain spaces. The three `Q2` tasks preserve their respective pointer/structure designs while allocating storage according to the entered count. `Q3` is a three-file program; compile `main.c` and `func.c` together. Its static array needs about 400 MB with 32-bit integers, so use a 64-bit process with enough memory.

Build just this lab from the course root:

```sh
cmake -S L10 -B build/L10
cmake --build build/L10
```

For a single target in the full course build: `cmake --build build --target l10_q1_task1`.
