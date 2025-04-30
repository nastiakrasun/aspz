// file: group_write_demo.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    const char *filename = "/tmp/shared_group_file.txt";

    // Створення файлу з правами rw-rw----
    int fd = open(filename, O_CREAT | O_WRONLY, 0660);
    if (fd < 0) {
        perror("Не вдалося створити файл");
        return 1;
    }

    // Запис у файл
    const char *text = "Цей файл створено користувачем A (власником), група має доступ до запису.\n";
    write(fd, text, strlen(text));
    close(fd);

    // Встановлюємо групу вручну через chown (виконати як root!)
    printf("Тепер запустіть команду як root для зміни групи файлу:\n");
    printf("sudo chown user1:sharedgroup %s\n", filename);
    printf("sudo chmod 660 %s\n", filename);
    printf("\nПотім увійдіть як інший користувач з цієї групи та виконайте:\n");
    printf("echo \"Додано user2.\" >> %s\n", filename);
    printf("cat %s\n", filename);

    return 0;
}
