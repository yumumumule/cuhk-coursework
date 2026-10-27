# ESTR1002 - C Programming

CUHK ESTR1002, Fall 2025. Solutions to all ten lab sheets, organised as
46 independently runnable exercises. Each lab keeps its original question sheet as
`description.pdf`, alongside its source files and input/output index.

## Exercise index

| Lab | Topics | Solutions | Handout |
| --- | --- | --- | --- |
| Lab1 | Output and arithmetic | [Source and question index](Lab1/README.md) | [PDF](Lab1/description.pdf) |
| Lab2 | Expressions and number conversion | [Source and question index](Lab2/README.md) | [PDF](Lab2/description.pdf) |
| Lab3 | Selection and numerical formulas | [Source and question index](Lab3/README.md) | [PDF](Lab3/description.pdf) |
| Lab4 | Loops and text patterns | [Source and question index](Lab4/README.md) | [PDF](Lab4/description.pdf) |
| Lab5 | Arrays and linear scans | [Source and question index](Lab5/README.md) | [PDF](Lab5/description.pdf) |
| Lab6 | Strings and character processing | [Source and question index](Lab6/README.md) | [PDF](Lab6/description.pdf) |
| Lab7 | Text decoding and numerical methods | [Source and question index](Lab7/README.md) | [PDF](Lab7/description.pdf) |
| Lab8 | Recursion and search | [Source and question index](Lab8/README.md) | [PDF](Lab8/description.pdf) |
| Lab9 | Dictionaries, dynamic programming and structures | [Source and question index](Lab9/README.md) | [PDF](Lab9/description.pdf) |
| Lab10 | Pointers, arrays and allocation | [Source and question index](Lab10/README.md) | [PDF](Lab10/description.pdf) |

## Layout and naming

```text
ESTR1002/
  Lab1/ ... Lab9/    description.pdf, Q1.c, Q2.c, ... and a question index
  Lab10/             description.pdf, Q1_task1.c, Q1_task2.c, ...
    Q3/              main.c, func.c, func.h
  cmake/             Shared compiler and target settings
  tests/             Example and boundary regression checks
  CMakeLists.txt     Build all lab exercises
  REVIEW.md          Review findings and validation record
```

Each ordinary `.c` file is a separate program with its own `main` function.
`Lab10/Q3` is the exception: its two source files form one program. The local game
project is excluded from this repository and from the course build.

## Compile and run

Use a C11 compiler. For example, from this directory:

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic Lab5/Q3.c -o l05_q3
./l05_q3
```

Link the math library for exercises using `<math.h>` when your Unix toolchain
requires it. For example:

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic Lab7/Q4.c -lm -o l07_q4
./l07_q4
```

Compile the multi-file exercise together:

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic Lab10/Q3/main.c Lab10/Q3/func.c -o l10_q3
./l10_q3
```

In Windows PowerShell, executable names normally end in `.exe`; run them using
`./l05_q3.exe` or `.\l05_q3.exe`. Use a UTF-8 terminal for `Lab7/Q2`.

### Build with CMake

Requires CMake 3.16 or newer and an available compiler/build toolchain:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
```

If you use MinGW-w64 on Windows, ensure its `bin` directory is on `PATH` and
select a matching generator, for example `-G "MinGW Makefiles"`, or `-G Ninja`
when Ninja is installed. MSVC users can use CMake's Visual Studio generator.

Targets are named `l01_q1`, `l01_q2`, ..., `l10_q2_task3`, and `l10_q3`.
For example, `cmake --build build --target l05_q3` builds one exercise.
Its executable is under `build/Lab5/`; the multi-file exercise is under
`build/Lab10/Q3/`. Visual Studio generators add a configuration subdirectory
such as `Debug/` or `Release/`. Each lab can also be configured independently;
see its README.

## Run the checks

Python 3.9+ enables the regression suite; no Python packages are needed.
CMake automatically registers it when a Python interpreter is found:

```sh
ctest --test-dir build --output-on-failure
```

For a Visual Studio build, add `-C Debug` or `-C Release` to match the configuration
built. If Python is not detected, configure with
`-DPython3_EXECUTABLE=/path/to/python` and rebuild.

The suite runs 462 checks across all 46 exercises, including the handout examples,
boundary inputs, seeded reference comparisons, and an independent test of the
maximum function with a five-element array. It also runs the normal 100-million
sample Monte Carlo program and 100-million-element maximum program. The latter
requires about 400 MB of memory on systems with 32-bit `int`.

Reviewed and verified on Windows with MinGW-w64 GCC 13.1.0, C11, and
`-Wall -Wextra -Wpedantic`: no compiler warnings. See [REVIEW.md](REVIEW.md)
for the corrections and scope of verification.
