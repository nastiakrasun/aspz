#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr = malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        arr[i] = i * i;
    }
    printf("Програма завершилася успішно.\n");

    // Спеціально не звільняємо пам'ять, щоб перевірити роботу Valgrind
    // free(arr);

    return 0;
}
