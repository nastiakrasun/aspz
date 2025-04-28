#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Відкриваємо FIFO для запису
    int fd = open("fifo_file", O_WRONLY);

    if (fd == -1) {
        perror("Failed to open FIFO for writing");
        return 1;
    }

    // Пишемо в FIFO
    const char *message = "Hello, FIFO!";
    ssize_t bytes_written = write(fd, message, 13); // Пишемо 13 байт

    if (bytes_written == -1) {
        perror("Failed to write to FIFO");
        close(fd);
        return 1;
    }

    printf("Message written to FIFO: %s\n", message);

    // Закриваємо FIFO
    close(fd);

    return 0;
}
