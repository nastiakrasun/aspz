#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    size_t step = 1024 * 1024; // Крок виділення пам’яті (1 МБ)
    size_t max_heap = 0;
    char *ptr;

    while (1) {
        ptr = (char *) malloc(max_heap + step);
        if (ptr == NULL) {
            break; // Виділення пам’яті не вдалося
        }
        free(ptr); // Звільняємо пам’ять перед наступною спробою
        max_heap += step;
    }

    printf("Максимальний розмір сегмента купи: %zu MB\n", max_heap / (1024 * 1024));
    return 0;
}
