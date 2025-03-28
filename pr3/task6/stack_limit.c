#include <stdio.h>

// Рекурсивна функція для демонстрації використання стеку
void recursiveFunction(int count) {
    // Вивести поточний лічильник рекурсії
    printf("Recursion depth: %d\n", count);

    // Рекурсивний виклик
    recursiveFunction(count + 1);
}

int main() {
    printf("Starting recursion...\n");
    recursiveFunction(1);  // Почати рекурсію з глибини 1
    return 0;
}
