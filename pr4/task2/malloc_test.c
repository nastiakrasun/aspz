#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    // Параметри для множення
    int xa = 100000;  // це значення може бути змінене
    int xb = 5000;    // це значення може бути змінене
    int num = xa * xb;  // Обчислення кількості байтів для виділення

    printf("Обчислений результат: %d\n", num);
    
    // Перевірка переповнення
    if (num < 0) {
        printf("Переповнення! Результат множення перевищує допустимий діапазон для int.\n");
        return 1;  // Завершити програму з помилкою
    }
    
    // Виділення пам'яті
    void *ptr = malloc(num);
    
    if (ptr == NULL) {
        printf("Не вдалося виділити пам'ять на %d байт.\n", num);
    } else {
        printf("Пам'ять успішно виділено на %d байт.\n", num);
        free(ptr);  // Звільняємо пам'ять
    }

    return 0;
}
