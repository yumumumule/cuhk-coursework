"""Optional independent equilibrium-set comparison against Nashpy.

Install tests/requirements.txt, then run: python tests/cross_check.py build/nash
Uses continuous random payoffs to avoid degenerate equilibrium continua.
"""
import warnings
import numpy as np
import nashpy as nash
from test_solver import EXE, solve

rng = np.random.default_rng(1005)
with warnings.catch_warnings():
    warnings.simplefilter("error")
    for case in range(150):
        m, n = int(rng.integers(1, 4)), int(rng.integers(1, 4))
        a, b = rng.normal(size=(m, n)), rng.normal(size=(m, n))
        if m == 1:
            expected = [(np.ones(1), np.eye(n)[np.argmax(b[0])])]
        elif n == 1:
            expected = [(np.eye(m)[np.argmax(a[:, 0])], np.ones(1))]
        else:
            # Nashpy's independent polytope-vertex algorithm, rather than
            # repeating the support-enumeration method used by our C solver.
            expected = list(nash.Game(a, b).vertex_enumeration())
        actual = solve(a.tolist(), b.tolist())["equilibria"]
        assert expected, f"Oracle returned no equilibrium in case {case}"
        assert len(actual) == len(expected), (case, actual, expected)
        for x, y in expected:
            assert any(np.allclose(x, eq["row_strategy"], atol=1e-7, rtol=0) and
                       np.allclose(y, eq["column_strategy"], atol=1e-7, rtol=0)
                       for eq in actual), (case, x, y, actual)
print(f"PASS: all equilibrium sets agree with Nashpy in 150 seeded random games ({EXE}).")
