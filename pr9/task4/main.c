#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("=== Команда whoami ===\n");
    int status1 = system("whoami");

    if (status1 == -1) {
        perror("Помилка виконання whoami");
        return 1;
    }

    printf("\n=== Команда id ===\n");
    int status2 = system("id");

    if (status2 == -1) {
        perror("Помилка виконання id");
        return 1;
    }

    return 0;
}
