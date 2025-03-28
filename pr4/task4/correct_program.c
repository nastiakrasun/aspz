#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = NULL;
    size_t n = 1024 * 1024 * 1024;  // Спробуємо виділити великий обсяг пам'яті

    while (1) {
        if (!ptr) {
            ptr = malloc(n);  // Спробуємо виділити пам'ять
        }

        if (ptr == NULL) {
            printf("Не вдалося виділити пам'ять.\n");
            break;  // Виходимо з циклу, якщо malloc не вдався
        }

        // Використання ptr
        printf("Виділено пам'ять на %p\n", ptr);

        // Завжди звільняємо пам'ять
        free(ptr);
        ptr = NULL;  // Встановлюємо ptr в NULL, щоб уникнути подвійного звільнення
    }

    return 0;
}

