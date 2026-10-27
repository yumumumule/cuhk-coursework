/* L07 Q4: Safeguarded Newton iteration, followed by quadratic deflation. */
#include <float.h>
#include <math.h>
#include <stdio.h>

static long double evaluate(long double x, long double b, long double c,
                            long double d) {
    return ((x + b) * x + c) * x + d;
}

static void quadratic(long double a, long double b, long double c) {
    if (a == 0.0L) {
        if (b != 0.0L) printf("%.6Lf\n", -c / b);
        else puts(c == 0.0L ? "Infinitely many solutions" : "No solution");
        return;
    }
    long double discriminant = b * b - 4.0L * a * c;
    long double tolerance = 64.0L * LDBL_EPSILON * (b * b + fabsl(4.0L * a * c));
    if (fabsl(discriminant) <= tolerance) discriminant = 0.0L;
    if (discriminant < 0.0L) {
        long double real = -b / (2.0L * a);
        long double imaginary = sqrtl(-discriminant) / (2.0L * fabsl(a));
        printf("%.6Lf+%.6Lfi\n%.6Lf-%.6Lfi\n", real, imaginary, real, imaginary);
    } else if (discriminant == 0.0L) {
        long double root = -b / (2.0L * a);
        printf("%.6Lf\n%.6Lf\n", root, root);
    } else {
        /* This form avoids cancellation when the two roots differ greatly. */
        long double q = -0.5L * (b + copysignl(sqrtl(discriminant), b));
        printf("%.6Lf\n%.6Lf\n", q / a, c / q);
    }
}

int main(void) {
    long double a, b, c, d;
    if (scanf("%Lf%Lf%Lf%Lf", &a, &b, &c, &d) != 4 ||
        !isfinite(a) || !isfinite(b) || !isfinite(c) || !isfinite(d)) return 1;
    if (a == 0.0L) {
        quadratic(b, c, d);
        return 0;
    }
    b /= a;
    c /= a;
    d /= a;
    if (!isfinite(b) || !isfinite(c) || !isfinite(d)) return 1;

    /* Cauchy's bound brackets every real root of this monic polynomial. */
    long double bound = 1.0L + fmaxl(fabsl(b), fmaxl(fabsl(c), fabsl(d)));
    long double low = -bound, high = bound, root = 0.0L;
    for (int iteration = 0; iteration < 512; iteration++) {
        long double value = evaluate(root, b, c, d);
        if (value == 0.0L) break;
        if (value < 0.0L) low = root;
        else high = root;
        long double derivative = (3.0L * root + 2.0L * b) * root + c;
        long double next = derivative == 0.0L ? (low + high) / 2.0L
                                             : root - value / derivative;
        /* Bisection keeps zero derivatives and divergent Newton steps safe. */
        if (!isfinite(next) || next <= low || next >= high) next = (low + high) / 2.0L;
        if (fabsl(next - root) <= 1e-15L * fmaxl(1.0L, fabsl(next))) {
            root = next;
            break;
        }
        root = next;
    }
    printf("%.6Lf\n", root);
    quadratic(1.0L, b + root, (root + b) * root + c);
    return 0;
}
