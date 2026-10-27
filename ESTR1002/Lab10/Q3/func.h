#ifndef L10_Q3_FUNC_H
#define L10_Q3_FUNC_H

/* The assignment uses 100 million integers (about 400 MB with 32-bit int). */
#ifndef SIZE
#define SIZE 100000000
#endif

struct foo {
    int a[SIZE];
};

void func(int a[]);

#endif
