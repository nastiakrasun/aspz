#include <stdio.h>

int main() {
    int a[3] = {1, 2, 3};  // Масив розміром 3
    int value = a[5];      // Читання елемента за межами масиву

    printf("Зчитане значення: %d\n", value); // Можливо — сміттєве, але не segfault

    return 0;
}