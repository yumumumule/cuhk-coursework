# Regression checks

Build the course from its root, then run:

```sh
ctest --test-dir build --output-on-failure
```

Python 3.9+ is required, with no third-party modules. There are 462 checks covering
all 46 exercise executables. Inputs include the handout examples, array and
string boundaries, negative data, empty/short cases where applicable, numerical
degeneracies and reproducible generated cases.

The suite finds executables recursively under the build directory, so it works
with the normal lab subdirectories and single-configuration or Visual Studio
output layouts. Use a build directory containing one configuration at a time.
For Visual Studio CTest runs, specify the built configuration with `-C`.

`l10_q3_max.c` links the actual `Lab10/Q3/func.c` with `SIZE=5`, allowing exact tests
for first/last maxima, negative values and equal values. The normal exercise is
also run with its original 100000000-element array. The environment exercises
run with synthetic values; the suite does not print the user's environment.

If running the script directly, supply `--build-dir` and `--boundary-exe`:

```sh
python tests/regression.py --build-dir build --boundary-exe build/l10_q3_boundary_test
```

On Windows add `.exe` to the boundary executable path. For multi-configuration
generators its path also includes the configuration directory.
