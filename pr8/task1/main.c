#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main() {
    const char *text = "Hello, this is a long text to demonstrate partial write.\n";
    int len = strlen(text);

    // Створимо пайп (канал)
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Робимо пайп неблокуючим
    int flags = fcntl(pipefd[1], F_GETFL);
    if (flags == -1) {
        perror("fcntl get");
        exit(EXIT_FAILURE);
    }
    if (fcntl(pipefd[1], F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl set");
        exit(EXIT_FAILURE);
    }

    // Намагатимемось записати великий буфер
    char big_buffer[1024 * 1024]; // 1 MB = 1048576 bytes
    memset(big_buffer, 'A', sizeof(big_buffer));

    ssize_t count = write(pipefd[1], big_buffer, sizeof(big_buffer));
    printf("Requested to write %lu bytes, actually wrote %zd bytes\n", sizeof(big_buffer), count);

    return 0;
}
