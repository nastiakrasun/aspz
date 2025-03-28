#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t max_size = (size_t)-1; // максимально можливе значення для size_t
    void *ptr;

    // Спробуємо виділити пам'ять розміром max_size
    ptr = malloc(max_size);
    
    if (ptr != NULL) {
        printf("Пам'ять успішно виділено!\n");
        free(ptr); // Звільняємо пам'ять
    } else {
        printf("Не вдалося виділити пам'ять.\n");
    }

    return 0;
}
