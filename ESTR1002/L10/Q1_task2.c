/* L10 Q1 Task 2: Print only the login name from the environment. */
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv, char **envp) {
    (void)argc;
    (void)argv;
    const char *fallback = NULL;
    while (*envp != NULL) {
        if (strncmp(*envp, "USERNAME=", 9) == 0) {
            puts(*envp + 9);
            return 0;
        }
        if (strncmp(*envp, "USER=", 5) == 0) fallback = *envp + 5;
        envp++;
    }
    /* Unix environments usually provide USER instead of USERNAME. */
    if (fallback != NULL) {
        puts(fallback);
        return 0;
    }
    return 1;
}
