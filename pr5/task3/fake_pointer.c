#include <stdio.h>

int main() {
    int x = 12345;
    
    // Помилково сприймаємо x як адресу і намагаємось читати з цієї адреси
    int value = *(int*)x;  // ❌ Undef. behavior: x не є дійсною адресою

    printf("Value: %d\n", value);

    return 0;
}
