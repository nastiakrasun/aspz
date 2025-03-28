#include <stdio.h>
#include <stdlib.h>

int main() {
    // Викликаємо malloc(0)
    void *ptr = malloc(0);

    // Перевіряємо, чи ptr не NULL
    if (ptr != NULL) {
        printf("malloc(0) повернув вказівник: %p\n", ptr);
    } else {
        printf("malloc(0) повернув NULL\n");
    }

    // Завжди звільняємо пам'ять, навіть якщо malloc(0) повернув NULL або валідну адресу
    free(ptr);
    printf("Пам'ять звільнена.\n");

    return 0;
}
