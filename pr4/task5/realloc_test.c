#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t large_size = (size_t)-1;  // Намагання виділити занадто великий блок
    int *ptr = malloc(10 * sizeof(int));
    
    if (!ptr) {
        perror("Initial malloc failed");
        return EXIT_FAILURE;
    }

    printf("Memory allocated successfully.\n");

    int *new_ptr = realloc(ptr, large_size);
    if (!new_ptr) {
        perror("Realloc failed");
        free(ptr);  // Важливо звільнити старий блок!
    } else {
        printf("Realloc succeeded unexpectedly!\n");
        free(new_ptr);
    }

    return EXIT_SUCCESS;
}
