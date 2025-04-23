#include <stdio.h>

int main() {
    int a[3] = {1, 2, 3};
    int value = a[5]; // переповнення масиву при читанні
    printf("Прочитано: %d\n", value);
    return 0;
}
