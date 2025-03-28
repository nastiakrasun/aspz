#include <stdio.h>
#include <stdlib.h>

struct sbar {
    int data;
};

int main() {
    struct sbar *ptr, *newptr;

    // Початкове виділення пам'яті
    ptr = calloc(1000, sizeof(struct sbar));
    if (!ptr) {
        perror("calloc failed");
        return EXIT_FAILURE;
    }

    // Перевиділення пам'яті за допомогою realloc
    newptr = realloc(ptr, 500 * sizeof(struct sbar));
    if (!newptr) {
        perror("realloc failed");
        free(ptr);  // Якщо realloc не вдалося, слід звільнити старий блок
        return EXIT_FAILURE;
    }

    printf("Memory reallocated successfully\n");

    free(newptr);
    return EXIT_SUCCESS;
}
