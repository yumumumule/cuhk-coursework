/* L01 Q2: Calculate a sphere's surface area and volume. */
#include <stdio.h>

int main(void) {
    const double pi = 3.1416;
    double radius;

    printf("Please enter the radius: ");
    if (scanf("%lf", &radius) != 1) {
        return 1;
    }
    double area = 4.0 * pi * radius * radius;
    double volume = area * radius / 3.0;
    printf("Area: %.4f\n", area);
    printf("Volume: %.4f\n", volume);
    return 0;
}
