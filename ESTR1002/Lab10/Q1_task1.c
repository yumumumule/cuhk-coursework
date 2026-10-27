/* L10 Q1 Task 1: Walk the environment with pointers, without subscripts. */
#include <stdio.h>

/* This third main parameter is an implementation extension used by the lab. */
int main(int argc, char **argv, char **envp) {
    (void)argc;
    (void)argv;
    while (*envp != NULL) {
        puts(*envp);
        envp++;
    }
    return 0;
}
