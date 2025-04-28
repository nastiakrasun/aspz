#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "testfile.bin";
    unsigned char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};

    // Створюємо файл і записуємо дані
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if (fd == -1) {
        perror("open for writing");
        exit(EXIT_FAILURE);
    }

    if (write(fd, data, sizeof(data)) != sizeof(data)) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);

    // Тепер відкриваємо файл для читання
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open for reading");
        exit(EXIT_FAILURE);
    }

    // Переміщуємо покажчик на 3-й байт
    if (lseek(fd, 3, SEEK_SET) == -1) {
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Читаємо 4 байти
    unsigned char buffer[4];
    ssize_t bytes_read = read(fd, buffer, 4);
    if (bytes_read == -1) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Buffer contents:\n");
    for (int i = 0; i < bytes_read; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    close(fd);
    return 0;
}
