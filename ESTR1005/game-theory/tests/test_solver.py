"""Black-box regression tests; only the Python standard library is required."""
import json
import math
from pathlib import Path
import random
import subprocess
import sys
import unittest

EXE = str(Path(sys.argv.pop(1)).resolve())
ROOT = Path(__file__).resolve().parents[1]


def solve(a, b):
    text = f"{len(a)} {len(a[0])}\n"
    text += "\n".join(" ".join(map(str, row)) for row in a + b)
    process = subprocess.run([EXE, "--json"], input=text, text=True, capture_output=True)
    if process.returncode:
        raise AssertionError(process.stderr)
    return json.loads(process.stdout)


def validate(test, result, a, b):
    """Recompute expected payoffs and every unilateral pure deviation."""
    m, n = len(a), len(a[0])
    test.assertGreater(len(result["equilibria"]), 0)
    test.assertEqual(result["support_pairs_checked"], ((1 << m) - 1) * ((1 << n) - 1))
    test.assertEqual(result["enumeration"], "representatives")
    for eq in result["equilibria"]:
        x, y = eq["row_strategy"], eq["column_strategy"]
        test.assertEqual((len(x), len(y)), (m, n))
        for distribution in (x, y):
            test.assertTrue(all(math.isfinite(p) and p >= 0 for p in distribution))
            test.assertAlmostEqual(sum(distribution), 1, places=12)
        scales = [max(abs(v) for row in matrix for v in row) or 1 for matrix in (a, b)]
        row_values = [sum(a[i][j] / scales[0] * y[j] for j in range(n)) for i in range(m)]
        col_values = [sum(b[i][j] / scales[1] * x[i] for i in range(m)) for j in range(n)]
        u = sum(x[i] * row_values[i] for i in range(m))
        v = sum(y[j] * col_values[j] for j in range(n))
        regrets = [max(0, max(row_values) - u), max(0, max(col_values) - v)]
        for prefix, regret, payoff, scale in zip(("row", "column"), regrets, (u, v), scales):
            test.assertLessEqual(regret, 1.0001e-8)
            test.assertAlmostEqual(eq[prefix + "_payoff"] / scale, payoff, places=12)
            test.assertAlmostEqual(eq[prefix + "_normalized_regret"], regret, places=12)
            test.assertAlmostEqual(eq[prefix + "_regret"] / scale, regret, places=12)


class SolverTests(unittest.TestCase):
    def test_rps(self):
        a = [[0, -1, 1], [1, 0, -1], [-1, 1, 0]]
        b = [[-v for v in row] for row in a]
        result = solve(a, b)
        validate(self, result, a, b)
        self.assertEqual(len(result["equilibria"]), 1)
        for key in ("row_strategy", "column_strategy"):
            for p in result["equilibria"][0][key]:
                self.assertAlmostEqual(p, 1 / 3)

    def test_battle_of_the_sexes(self):
        a, b = [[2, 0], [0, 1]], [[1, 0], [0, 2]]
        result = solve(a, b)
        validate(self, result, a, b)
        self.assertEqual(len(result["equilibria"]), 3)
        mixed = [eq for eq in result["equilibria"] if eq["type"] == "mixed"]
        self.assertEqual(len(mixed), 1)
        self.assertAlmostEqual(mixed[0]["row_strategy"][0], 2 / 3)
        self.assertAlmostEqual(mixed[0]["column_strategy"][0], 1 / 3)

    def test_prisoners_dilemma(self):
        a, b = [[3, 0], [5, 1]], [[3, 5], [0, 1]]
        result = solve(a, b)
        validate(self, result, a, b)
        self.assertEqual(len(result["equilibria"]), 1)
        self.assertEqual(result["equilibria"][0]["row_strategy"], [0, 1])
        self.assertEqual(result["equilibria"][0]["column_strategy"], [0, 1])

    def test_zero_sum_flag(self):
        process = subprocess.run([EXE, "--zero-sum", "--json", "--file",
                                  str(ROOT / "examples/zero_sum_legacy.txt")],
                                 text=True, capture_output=True, check=True)
        self.assertEqual(len(json.loads(process.stdout)["equilibria"]), 1)

    def test_all_zero_and_identical_payoffs(self):
        for value in (0, 5, -3):
            a = [[value] * 3 for _ in range(3)]
            result = solve(a, a)
            validate(self, result, a, a)
            self.assertEqual(len(result["equilibria"]), 9)

    def test_unequal_support_degeneracy(self):
        # Column action 3 pays 1 against every row mixture; only x=(.5,.5)
        # prevents a profitable column deviation when it is played alone.
        a = [[1, -1, 0], [-1, 1, 0]]
        b = [[0, 2, 1], [2, 0, 1]]
        result = solve(a, b)
        validate(self, result, a, b)
        self.assertTrue(any(sum(p > 1e-8 for p in eq["row_strategy"]) == 2
                            and sum(p > 1e-8 for p in eq["column_strategy"]) == 1
                            for eq in result["equilibria"]))

    def test_single_action_and_rectangular_games(self):
        for a, b in [([[7]], [[-2]]), ([[1, 2, 3]], [[3, 2, 1]]),
                     ([[1], [3], [2]], [[0], [4], [1]]),
                     ([[1, 1, -1], [2, -1, 0]], [[.5, -1, -.5], [-1, 3, 2]])]:
            validate(self, solve(a, b), a, b)

    def test_scaling_and_pivoting(self):
        base = [[0, -1, 1], [1, 0, -1], [-1, 1, 0]]
        for scale_a, scale_b in [(1e90, 1e-90), (1e-90, 1e90), (1, 1)]:
            a = [[scale_a * v for v in row] for row in base]
            b = [[-scale_b * v for v in row] for row in base]
            result = solve(a, b)
            validate(self, result, a, b)
            self.assertEqual(len(result["equilibria"]), 1)

    def test_seeded_random_games(self):
        rng = random.Random(1005)
        for case in range(300):
            m, n = rng.randint(1, 3), rng.randint(1, 3)
            generator = (lambda: rng.randint(-3, 3)) if case % 2 else (lambda: rng.uniform(-5, 5))
            a = [[generator() for _ in range(n)] for _ in range(m)]
            b = [[generator() for _ in range(n)] for _ in range(m)]
            with self.subTest(case=case):
                validate(self, solve(a, b), a, b)

    def test_invalid_input(self):
        cases = ["", "4 3", "0 2", "2.0 2", "-1 1", "1 1 5", "1 1 nan 2",
                 "1 1 inf 2", "1 1 1e101 2", "1 1 1e-999 2", "1 1 x 2",
                 "1 1 1 2 extra", "1 1 " + "1" * 150 + " 2"]
        for text in cases:
            with self.subTest(text=text[:40]):
                process = subprocess.run([EXE, "--json"], input=text, text=True, capture_output=True)
                self.assertEqual(process.returncode, 1)
                self.assertEqual(process.stdout, "")
                self.assertIn("Invalid input", process.stderr)

    def test_cli_options(self):
        for args in (["--wat"], ["--file"], ["--json", "--json"],
                     ["--file", str(ROOT / "not-a-real-file.txt")]):
            process = subprocess.run([EXE, *args], text=True, capture_output=True)
            self.assertEqual(process.returncode, 1)
        self.assertEqual(subprocess.run([EXE, "--help"], capture_output=True).returncode, 0)

    def test_examples_and_human_output(self):
        for path in (ROOT / "examples").glob("*.txt"):
            args = [EXE, "--file", str(path)]
            if path.stem == "zero_sum_legacy":
                args.append("--zero-sum")
            process = subprocess.run(args, text=True, capture_output=True)
            self.assertEqual(process.returncode, 0, process.stderr)
            self.assertIn("Equilibrium", process.stdout)
            self.assertIn("representatives", process.stdout)


if __name__ == "__main__":
    unittest.main()
