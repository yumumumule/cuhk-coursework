/* L09 Q4: Recover a containing structure using a member's byte offset. */
#include <stddef.h>
#include <stdio.h>

struct foo {
    char c1;
    int i;
    char c2;
    double d;
};

void func(double *d) {
    /* offsetof accounts for padding chosen by the compiler and platform. */
    const struct foo *owner = (const struct foo *)((const char *)d - offsetof(struct foo, d));
    printf("%d\n", owner->i);
}

int main(void) {
    struct foo bar = {0};
    bar.i = 10;
    func(&bar.d);
    return 0;
}
