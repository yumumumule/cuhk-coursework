/* L09 Q1: Sort a case-insensitive dictionary and suppress shared prefixes. */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Grow words dynamically because the exercise specifies no length limit. */
static char *read_word(void) {
    int ch;
    do {
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));
    if (ch == EOF) return NULL;
    size_t length = 0, capacity = 32;
    char *word = malloc(capacity);
    if (word == NULL) exit(EXIT_FAILURE);
    do {
        if (length + 1 == capacity) {
            capacity *= 2;
            char *larger = realloc(word, capacity);
            if (larger == NULL) {
                free(word);
                exit(EXIT_FAILURE);
            }
            word = larger;
        }
        word[length++] = (char)tolower((unsigned char)ch);
        ch = getchar();
    } while (ch != EOF && !isspace((unsigned char)ch));
    word[length] = '\0';
    return word;
}

static int compare_words(const void *left, const void *right) {
    const char *const *a = left;
    const char *const *b = right;
    return strcmp(*a, *b);
}

int main(void) {
    size_t count = 0, capacity = 16;
    char **words = malloc(capacity * sizeof(*words));
    if (words == NULL) return 1;
    char *word;
    while ((word = read_word()) != NULL) {
        if (strcmp(word, "bye") == 0) {
            free(word);
            break;
        }
        if (count == capacity) {
            capacity *= 2;
            char **larger = realloc(words, capacity * sizeof(*words));
            if (larger == NULL) {
                free(word);
                for (size_t i = 0; i < count; i++) free(words[i]);
                free(words);
                return 1;
            }
            words = larger;
        }
        words[count++] = word;
    }
    qsort(words, count, sizeof(*words), compare_words);
    for (size_t i = 0; i < count; i++) {
        if (i > 0 && strcmp(words[i], words[i - 1]) == 0) continue;
        size_t prefix = 0;
        if (i > 0) {
            while (words[i][prefix] != '\0' && words[i][prefix] == words[i - 1][prefix]) prefix++;
        }
        for (size_t j = 0; j < prefix; j++) putchar(' ');
        puts(words[i] + prefix);
    }
    for (size_t i = 0; i < count; i++) free(words[i]);
    free(words);
    return 0;
}
