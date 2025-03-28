#include <stdio.h>
#include <stdlib.h>

struct sbar {
    int data;
};

int main() {
    struct sbar *ptr, *newptr;

    // Використовуємо calloc для початкового виділення
    ptr = calloc(1000, sizeof(struct sbar));
    if (!ptr) {
        perror("calloc failed");
        return EXIT_FAILURE;
    }

    // Використовуємо reallocarray для перевиділення
    newptr = reallocarray(ptr, 500, sizeof(struct sbar));
    if (!newptr) {
        perror("reallocarray failed");
        free(ptr); // Звільняємо старий блок, якщо новий не виділився
        return EXIT_FAILURE;
    }

    printf("Memory reallocated successfully\n");

    free(newptr);
    return EXIT_SUCCESS;
}
