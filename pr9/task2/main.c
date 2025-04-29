#include <stdio.h>
#include <stdlib.h>

int main() {
    int status;

    printf("Спроба виконати 'cat /etc/shadow' як root...\n");

    status = system("sudo cat /etc/shadow");

    if (status == -1) {
        perror("system");
        return 1;
    } else {
        printf("\nКоманда завершена з кодом: %d\n", WEXITSTATUS(status));
    }

    return 0;
}
