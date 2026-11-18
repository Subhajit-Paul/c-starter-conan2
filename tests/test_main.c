#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    const int values[] = {2, 4, 6};
    int total = 0;
    for (size_t i = 0; i < sizeof values / sizeof values[0]; ++i) {
        total += values[i];
    }
    if (total != 12) {
        fprintf(stderr, "Expected array sum 12, got %d\n", total);
        return EXIT_FAILURE;
    }

    const char word[] = "hello";
    size_t length = strlen(word);
    if (length != 5) {
        fprintf(stderr, "Expected string length 5, got %zu\n", length);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
