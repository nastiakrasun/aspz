#include <stdio.h>
#include <stdlib.h>

int main() {
    // 1. Виклик realloc(NULL, size) -> еквівалент malloc(size)
    int *ptr1 = realloc(NULL, 10 * sizeof(int));
    if (ptr1) {
        printf("realloc(NULL, 10*sizeof(int)) succeeded: %p\n", (void *)ptr1);
        free(ptr1);
    } else {
        perror("realloc(NULL, 10*sizeof(int)) failed");
    }

    // 2. Виклик realloc(ptr, 0) -> поведінка залежить від реалізації
    int *ptr2 = malloc(10 * sizeof(int));
    if (!ptr2) {
        perror("Initial malloc failed");
        return EXIT_FAILURE;
    }

    int *ptr3 = realloc(ptr2, 0);
    if (!ptr3) {
        printf("realloc(ptr, 0) returned NULL, possible free(ptr).\n");
    } else {
        printf("realloc(ptr, 0) returned %p (implementation-defined behavior)\n", (void *)ptr3);
        free(ptr3);  // Якщо realloc не повернув NULL, треба звільнити пам'ять.
    }

    return EXIT_SUCCESS;
}
