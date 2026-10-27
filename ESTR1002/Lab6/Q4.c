/* L06 Q4: Rotate the vowel sequence while preserving each vowel's case. */
#include <stdio.h>
#include <string.h>

int main(void) {
    char text[201], vowels[201];
    int positions[200], count = 0, shift;
    if (scanf("%200s%d", text, &shift) != 2) return 1;
    for (int i = 0; text[i] != '\0'; i++) {
        if (strchr("aeiouAEIOU", text[i]) != NULL) {
            positions[count] = i;
            vowels[count++] = text[i];
        }
    }
    if (count > 0) {
        /* Reduce before adding count so even very large shifts stay safe. */
        shift = (shift % count + count) % count;
        for (int i = 0; i < count; i++) text[positions[i]] = vowels[(i + shift) % count];
    }
    puts(text);
    return 0;
}
