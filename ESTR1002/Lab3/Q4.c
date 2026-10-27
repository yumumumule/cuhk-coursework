/* L03 Q4: Convert RGB components to normalised HSV components. */
#include <stdio.h>

int main(void) {
    double red, green, blue;
    if (scanf("%lf%lf%lf", &red, &green, &blue) != 3) {
        return 1;
    }
    red /= 255.0;
    green /= 255.0;
    blue /= 255.0;
    double maximum = red;
    double minimum = red;
    if (green > maximum) maximum = green;
    if (blue > maximum) maximum = blue;
    if (green < minimum) minimum = green;
    if (blue < minimum) minimum = blue;

    double range = maximum - minimum;
    double saturation = maximum == 0.0 ? 0.0 : range / maximum;
    double hue = 0.0;
    if (range != 0.0) {
        if (maximum == red) {
            hue = (green - blue) / range;
        } else if (maximum == green) {
            hue = 2.0 + (blue - red) / range;
        } else {
            hue = 4.0 + (red - green) / range;
        }
        hue /= 6.0;
        if (hue < 0.0) hue += 1.0;
    }
    printf("%.3f\n%.3f\n%.3f\n", hue, saturation, maximum);
    return 0;
}
