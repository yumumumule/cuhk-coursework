"""Run assignment examples, boundary cases and seeded reference comparisons.

Requires Python 3.9+ and a completed CMake build. No third-party packages are used.
"""
import argparse
import calendar
import cmath
import colorsys
import math
import os
from pathlib import Path
import random
import re
import subprocess


parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("--build-dir", type=Path, required=True)
parser.add_argument("--boundary-exe", type=Path, required=True)
args = parser.parse_args()
executables = {
    p.stem: p for p in args.build_dir.rglob("*")
    if p.is_file() and re.fullmatch(r"l\d{2}_q\d(?:_task\d)?", p.stem)
    and (p.suffix == ".exe" if os.name == "nt" else p.suffix == "")
}
checks = 0
covered = set()
rng = random.Random(1002)


def run(target, data="", env=None, timeout=10):
    global checks
    result = subprocess.run([str(executables[target])], input=data.encode("utf-8"),
                            stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                            timeout=timeout, env=env)
    assert result.returncode == 0, (target, "exit status", result.returncode,
                                    result.stderr.decode("utf-8", errors="replace"))
    checks += 1
    covered.add(target)
    return result.stdout.decode("utf-8").replace("\r\n", "\n")


def expect(target, data, expected):
    actual = run(target, data)
    assert actual == expected, (target, repr(data[:120]), repr(actual), repr(expected))


expect("l01_q1", "", "Hello world!\nWelcome to ESTR1002!\n")
expect("l01_q2", "2.57\n", "Please enter the radius: Area: 82.9998\nVolume: 71.1032\n")
expect("l01_q2", "0\n", "Please enter the radius: Area: 0.0000\nVolume: 0.0000\n")
expect("l01_q3", "", '       .\n      ":"\n    ___:____     |"\\/"|\n'
       "  ,'        `.    \\  /\n  |  o        \\___/  |\n~^~^~^~^~^~^~^~^~^~^~^~^~\n")
expect("l02_q1", "10\n", "25.4\n")
expect("l02_q2", "1.0\n", "0.45\n")
expect("l02_q2", "0\n", "0.00\n")
for number in range(16):
    expect("l02_q3", f"{number:04b}\n", f"{number}\n")
    expect("l02_q4", f"{number}\n", f"{number:04b}\n")

for neck in range(3, 8):
    lines = ["  ^YY", " {oo >", '(""  |']
    lines += [" " * (i + 3) + "\\  \\" for i in range(neck)]
    lines[-1] += " -----"
    lines += [" " * (neck + 2) + "(         )\\",
              " " * (neck + 3) + "\\_______/  \\",
              " " * (neck + 4) + "|-| |-|    }",
              " " * (neck + 4) + "|_| |_|"]
    expect("l03_q1", f"{neck}\n", "\n".join(lines) + "\n")
for hours in [0, 100, 132, 133, 160, 168, 169, 321, 500]:
    gross = min(hours, 160) * 75.5 + max(0, hours - 160) * 75.5 * 1.5
    tax = min(gross, 10000) * .1 + min(max(gross - 10000, 0), 3000) * .16
    tax += max(gross - 13000, 0) * .23
    values = [float(s.split("=")[1]) for s in run("l03_q2", f"{hours}\n").splitlines()]
    assert all(abs(a - b) < .0051 for a, b in zip(values, [gross, tax, gross - tax]))
for departure, arrival in [(1001, 1320), (650, 1303), (2345, 55), (1050, 1005),
                            (0, 0), (2359, 0), (1000, 959)]:
    minutes = lambda t: t // 100 * 60 + t % 100
    duration = (minutes(arrival) - minutes(departure)) % 1440 or 1440
    expect("l03_q3", f"{departure} {arrival}\n", f"{duration}\n")
for rgb in [(205, 192, 176), (240, 248, 255), (0, 0, 0), (255, 255, 255),
            (255, 0, 0), (0, 255, 0), (0, 0, 255), (255, 0, 255), (255, 255, 0)] + [
                tuple(rng.randrange(256) for _ in range(3)) for _ in range(20)]:
    hsv = colorsys.rgb_to_hsv(*(v / 255 for v in rgb))
    actual = list(map(float, run("l03_q4", " ".join(map(str, rgb)) + "\n").split()))
    assert len(actual) == 3 and all(abs(a - b) < .00051 for a, b in zip(actual, hsv))
for decimal, alien in [(31, 25), (25, 31), (31, 1), (1, 1), (9, 9), (10, 10),
                        (5, 10), (2, 2), (15, 12), (999, 999)] + [
                            (rng.randint(1, 999), rng.randint(1, 999)) for _ in range(80)]:
    digits = [int(ch) for ch in str(alien)]
    answer = "CHEATED"
    for base in range(max(2, max(digits) + 1), 1001):
        value = 0
        for digit in digits:
            value = value * base + digit
        if value == decimal:
            answer = str(base)
            break
    expect("l03_q5", f"{decimal} {alien}\n", answer + "\n")

for number in [0, 1, 1110, 123, 1111111, 5000000]:
    expect("l04_q1", f"{number}\n", f"{str(number).count('1')}\n")
for size in [1, 3, 5, 15]:
    expected = "".join(",".join(map(str, range(row, 0, -1))) + "\n" for row in range(size, 0, -1))
    expect("l04_q2", f"{size}\n", expected)
for weekday in range(7):
    for days in [28, 31]:
        # calendar uses Monday=0; the assignment uses Sunday=0.
        cal = calendar.Calendar(firstweekday=6)
        year, month = next((y, m) for y in range(2000, 2050) for m in range(1, 13)
                           if (calendar.monthrange(y, m)[0] + 1) % 7 == weekday
                           and calendar.monthrange(y, m)[1] == days)
        lines = ["Su Mo Tu We Th Fr Sa"]
        lines += [" ".join(f"{day:2d}" if day else "  " for day in week).rstrip()
                  for week in cal.monthdayscalendar(year, month)]
        expect("l04_q3", f"{weekday} {days}\n", "\n".join(lines) + "\n")
expect("l04_q4", "3\n", "x..x..x\n.x.x.x.\n..xxx..\nxxxxxxx\n..xxx..\n.x.x.x.\nx..x..x\n")
expect("l04_q5", "1\n", "....*\n...*.*\n..*****\n.*.....*\n*.......*\n")
expect("l04_q5", "3\n", "........*\n.......*.*\n......*...*\n.....*.....*\n....*********\n"
       "...*.........*\n..*...........*\n.*.............*\n*...............*\n")
for size in [1, 8, 9, 11, 100]:
    triangular = {i * (i + 1) // 2 for i in range(1, size + 1)}
    rows = ["".join("@" if row % 2 and col in triangular else
                    "#" if row % 2 or col in triangular else "."
                    for col in range(1, size + 1)) for row in range(1, size + 1)]
    expect("l04_q6", f"{size}\n", "\n".join(rows) + "\n")

for n in range(13):
    for k in range(n + 1):
        expect("l05_q1", f"{n} {k}\n", f"{math.comb(n, k)}\n")
expect("l05_q2", "1\n", "1\n")
expect("l05_q2", "4\n", "1,\t2,\t3,\t4\n2,\t3,\t4,\t5\n3,\t4,\t5,\t6\n4,\t5,\t6,\t7\n")
arrays = [[-2, 5, -2], [-7, 1, 5, 2, -4, 3, 0], [1, 3, 5], [0] * 20000,
          [2147483647, 0, 2147483647]]
arrays += [[rng.randint(-50, 50) for _ in range(rng.randint(3, 50))] for _ in range(20)]
for values in arrays:
    total, left, indices = sum(values), 0, []
    for i, value in enumerate(values):
        if left == total - left - value:
            indices.append(str(i))
        left += value
    expect("l05_q3", f"{len(values)}\n" + " ".join(map(str, values)) + "\n",
           (" ".join(indices) if indices else "-1") + "\n")
for values, answer in [([1], 0), ([1, 2], 0), ([1, 2, 3, 2, 1, 2], 4),
                        ([3, 2, 5, 8, 6, 9, 8, 7, 6, 9], 31), ([1, 2, 2, 2, 1], 0),
                        ([2147483647, -2147483648, 2147483647], -2147483648)]:
    expect("l05_q4", f"{len(values)}\n" + " ".join(map(str, values)) + "\n", f"{answer}\n")
for data, answer in [("4 5\n5 3 3 3 3 3\n", "5"), ("0 -1\n6 3 4 1 3 3 1\n", "2"),
                      ("2 10\n6 4 3 4 4 3 4\n", "impossible"), ("0 0\n0\n", "0"),
                      ("1000 1000\n2000 " + " ".join(["3"] * 2000) + "\n", "1000")]:
    expect("l05_q5", data, answer + "\n")

for password, answer in [("password", "no"), ("PASSword123", "no"),
                          ('P"eNm\\ga7=W;VQm', "yes"), ("abcdef!", "no"),
                          ("ABCDE1!", "no"), ("Abcde1+", "no"),
                          ("Aa1!" + "x" * 26, "yes")]:
    expect("l06_q1", password + "\n", answer + "\n")
for text, expected in [("aaackhhGGGg", "a3ckh2G3g"), ("AbcdC#$", "AbcdC#$"),
                        ("a" * 2000, "a2000"), ("a", "a"), ("!!aBB", "!2aB2")]:
    expect("l06_q2", text + "\n", expected + "\n")
for first, second, answer in [("Torch Wood", "Doctor Who", "yes"),
                              ("TOM MARVOLO RIDDLE", "I AM LORD VOLDEMORT", "yes"),
                              ("OK YOU WIN", "USE WINDOW", "no"), ("abc", "def", "no"),
                              ("a" * 1000, "A" * 1000, "yes"), ("ab", "aa", "no")]:
    expect("l06_q3", first + "\n" + second + "\n", answer + "\n")
for text, shift, answer in [("hEllo", 1, "hollE"), ("aeiou", 2, "iouae"),
                            ("codetEsthAha", -2, "cAdatosthehE"), ("rhythm", 99, "rhythm"),
                            ("aeiou", 2147483647, "iouae"), ("aeiou", -2147483648, "iouae")]:
    expect("l06_q4", f"{text}\n{shift}\n", answer + "\n")
for text, value in [("11001001", 201), ("cats", 75), ("zig", 11), ("a", 1),
                     ("aaaa", 15), ("ab", 2), ("a" * 59, 2 ** 59 - 1)]:
    expect("l06_q5", text + "\n", f"{value}\n")

expect("l07_q1", "Alpe\n1 3 3 2 4\n", "apple\n")
expect("l07_q1", "The quick brown fox jumps over the lazy dog\n25 1 3 28 3 4 21 13 11 25\n", "steve jobs\n")
expect("l07_q1", "A" * 199 + "Z\n200 1\n", "za\n")
expect("l07_q2", "", "日\nA\n")
pi = float(run("l07_q3", timeout=45))
assert abs(pi - math.pi) < .005, ("Monte Carlo estimate", pi)


def polynomial_roots(coefficients, expected):
    output = run("l07_q4", " ".join(map(str, coefficients)) + "\n")
    roots = [complex(line.replace("i", "j")) for line in output.splitlines()]
    assert len(roots) == len(expected), (coefficients, output)
    unmatched = list(expected)
    for root in roots:
        closest = min(range(len(unmatched)), key=lambda i: abs(root - unmatched[i]))
        wanted = unmatched.pop(closest)
        assert abs(root - wanted) <= 3e-5 * max(1, abs(wanted)), (coefficients, output, expected)


for coefficients, roots in [([1, -6, 11, -6], [1, 2, 3]), ([1, 0, 0, -1], [1, complex(-.5, math.sqrt(3)/2), complex(-.5, -math.sqrt(3)/2)]),
                            ([1, -3, 3, -1], [1, 1, 1]), ([1, 0, -3, 2], [-2, 1, 1]),
                            ([1, 0, -2, 2], [-1.7692923542, complex(.8846461771, .5897428050), complex(.8846461771, -.5897428050)]),
                            ([1, 0, 0, 0], [0, 0, 0]), ([0, 1, -5, 6], [2, 3]),
                            ([0, 1, 0, 1], [1j, -1j]), ([0, 0, 2, -4], [2]),
                            ([1, -1, 0, 0], [0, 0, 1])]:
    polynomial_roots(coefficients, roots)
for _ in range(20):
    roots = rng.sample(range(-20, 21), 3)
    x, y, z = roots
    polynomial_roots([1, -(x + y + z), x*y + x*z + y*z, -x*y*z], roots)
expect("l07_q4", "0 0 0 0\n", "Infinitely many solutions\n")
expect("l07_q4", "0 0 0 1\n", "No solution\n")

fibonacci = [1, 1]
for _ in range(39):
    fibonacci.append(sum(fibonacci[-2:]))
for n in [1, 2, 3, 10, 40]:
    expect("l08_q1", f"{n}\n", f"{fibonacci[n]}\n")
# Enumerate compositions of each nine-cell displacement and interleave runs.
chess_paths = sum(math.comb(8, horizontal - 1) * math.comb(8, vertical - 1)
                  * math.comb(horizontal + vertical, horizontal)
                  for horizontal in range(1, 10) for vertical in range(1, 10))
expect("l08_q2", "", f"{chess_paths}\n")
for grid, answer in [([[0, 1], [2, 0]], 2), ([[2, -3, 5], [-9, 0, 4], [93, 1, 3]], 90),
                      ([[-1, -2], [-3, -4]], -7), ([[1] * 11 for _ in range(11)], 21)]:
    data = f"{len(grid)-1}\n" + "\n".join(" ".join(map(str, row)) for row in grid) + "\n"
    expect("l08_q3", data, f"{answer}\n")
# Independent GF(2) span enumeration checks the puzzle's reachable states.
reachable_states = {0}
for row in range(4):
    for col in range(4):
        mask = sum(1 << (r * 4 + c) for r in range(4) for c in range(4) if r == row or c == col)
        reachable_states |= {state ^ mask for state in tuple(reachable_states)}
for state in [0, 1, 65535, 12345] + [rng.randrange(65536) for _ in range(6)]:
    data = " ".join(str((state >> i) & 1) for i in range(16)) + "\n"
    expect("l08_q4", data, "yes\n" if state in reachable_states else "no\n")

expect("l09_q1", "appLicaTion   Zoo   a    banana\nbatman an baMboO battle Applying\napply boTTle ByE\n",
       "a\n n\n pplication\n    y\n     ing\nbamboo\n  nana\n  tman\n   tle\n ottle\nzoo\n")
expect("l09_q1", "BYE\n", "")
expect("l09_q1", "APPLE apple apPle banana bye\n", "apple\nbanana\n")
expect("l09_q1", "a" * 1000 + " bye\n", "a" * 1000 + "\n")
for first, second, distance in [("kitten", "sitting", 3), ("trolley", "tolling", 4),
                                ("abcdefghij", "abcdefghij", 0), ("a b", "ab", 1),
                                ("", "abcdefghij", 10), ("", "", 0), ("a ", "a", 1)]:
    expect("l09_q2", first + "\n" + second + "\n", f"{distance}\n")
mazes = [([
    "###########", "#   #     #", "# #### # ##", "#      #  #", "### ###   #",
    "#   ##  ###", "# ###   ###", "# # # ### #", "# ### # # #", "#   #     #", "###########"], 1),
    (["###########", "#   #     #", "# ###### ##", "#      #  #", "#######   #",
      "#   ##  ###", "# ###   ###", "# # # ### #", "# ### # # #", "#   #   # #", "###########"], 0)]
for maze, answer in mazes:
    expect("l09_q3", "\n".join(maze) + "\n", f"{answer}\n")
expect("l09_q4", "", "10\n")

# Supply only test environment values, so no user environment contents are logged.
test_env = {key: os.environ[key] for key in ("PATH", "SystemRoot", "WINDIR") if key in os.environ}
test_env.update(USERNAME="Example Student", USER="unix_student", ESTR1002_TEST_MARKER="pointer_walk")
environment_lines = run("l10_q1_task1", env=test_env).splitlines()
assert "ESTR1002_TEST_MARKER=pointer_walk" in environment_lines
assert run("l10_q1_task2", env=test_env) == "Example Student\n"
del test_env["USERNAME"]
assert run("l10_q1_task2", env=test_env) == "unix_student\n"
for task in range(1, 4):
    target = f"l10_q2_task{task}"
    expect(target, "3\nGeorge Bush\nBill Gates\nSteve Jobs\n", "Steve Jobs\nBill Gates\nGeorge Bush\n")
    expect(target, "0\n", "")
    expect(target, "2\nABCDEFGHIJKLMN\nZ\n", "Z\nABCDEFGHIJKLMN\n")
    expect(target, "2\n\nWith Space\n", "With Space\n\n")
maximum = int(run("l10_q3", timeout=45))
assert maximum >= 0
boundary = subprocess.run([str(args.boundary_exe)], stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=10)
assert boundary.returncode == 0
assert boundary.stdout.decode().replace("\r\n", "\n") == "99\n99\n-5\n7\n"
checks += 4
assert covered == set(executables), ("Missing exercise coverage", set(executables) - covered)
assert len(covered) == 46, ("Expected 46 exercise executables", len(covered))
print(f"PASS: {checks} checks across all {len(covered)} exercise executables.")
print("Includes full-size Monte Carlo and 100-million-element maximum runs.")
