#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    const char *fifo_name = "/tmp/myfifo";
    char buffer[] = "Hello, FIFO!";

    // Створюємо FIFO (якщо вона ще не існує)
    if (mkfifo(fifo_name, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    // Відкриваємо FIFO для запису
    int fd = open(fifo_name, O_WRONLY | O_NONBLOCK); // Неблокуючий режим
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Спробуємо записати в FIFO
    ssize_t count = write(fd, buffer, strlen(buffer));
    if (count == -1) {
        perror("write");
    } else {
        printf("Записано %zd байт до FIFO\n", count);
    }

    close(fd);
    unlink(fifo_name); // Видалення FIFO
    return 0;
}
