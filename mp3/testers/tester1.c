/**
 * Malloc
 * CS 240 - Fall 2020
 */
#include "tester-utils.h"

#define NUM_CYCLES 10000000

int main() {
    int i;
    for (i = 0; i < NUM_CYCLES; i++) {
        int *ptr = malloc(sizeof(int));

        if (ptr == NULL) {
            fprintf(stderr, "Memory failed to allocate!\n");
            return 1;
        }

        *ptr = 4;
        free(ptr);
    }

    fprintf(stderr, "Memory was allocated, used, and freed!\n");
    return 0;
}
