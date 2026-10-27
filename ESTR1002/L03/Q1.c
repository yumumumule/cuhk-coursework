/* L03 Q1: Draw a giraffe with a neck length from 3 to 7. */
#include <stdio.h>

int main(void) {
    int num;
    if (scanf("%d", &num) != 1 || num < 3 || num > 7) {
        return 1;
    }
    printf("  ^YY\n {oo >\n(\"\"  |\n   \\  \\\n    \\  \\\n");
    switch (num - 3) {
        case 0:
            printf("     \\  \\ -----\n");
            printf("     (         )\\\n      \\_______/  \\\n       |-| |-|    }\n       |_| |_|");
            break;
        case 1:
            printf("     \\  \\\n      \\  \\ -----\n");
            printf("      (         )\\\n       \\_______/  \\\n        |-| |-|    }\n        |_| |_|");
            break;
        case 2:
            printf("     \\  \\\n      \\  \\\n       \\  \\ -----\n");
            printf("       (         )\\\n        \\_______/  \\\n         |-| |-|    }\n         |_| |_|");
            break;
        case 3:
            printf("     \\  \\\n      \\  \\\n       \\  \\\n        \\  \\ -----\n");
            printf("        (         )\\\n         \\_______/  \\\n          |-| |-|    }\n          |_| |_|");
            break;
        case 4:
            printf("     \\  \\\n      \\  \\\n       \\  \\\n        \\  \\\n         \\  \\ -----\n");
            printf("         (         )\\\n          \\_______/  \\\n           |-| |-|    }\n           |_| |_|");
            break;
    }
    putchar('\n');
    return 0;
}
