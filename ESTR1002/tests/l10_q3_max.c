/* Exercise the actual maximum function with maxima at both array boundaries. */
#include "func.h"

int main(void) {
    int last[SIZE] = {1, 2, 3, 4, 99};
    int first[SIZE] = {99, 4, 3, 2, 1};
    int negative[SIZE] = {-9, -8, -7, -6, -5};
    int repeated[SIZE] = {7, 7, 7, 7, 7};
    func(last);
    func(first);
    func(negative);
    func(repeated);
    return 0;
}
