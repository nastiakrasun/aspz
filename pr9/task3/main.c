#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    const char *orig_file = "/tmp/user_file.txt";
    const char *copy_file = "/home/nastia/copied_by_root.txt";

    // 1. Створення файлу від імені звичайного користувача
    FILE *fp = fopen(orig_file, "w");
    if (fp == NULL) {
        perror("Не вдалося створити файл");
        return 1;
    }
    fprintf(fp, "Це файл, створений звичайним користувачем.\n");
    fclose(fp);
    printf("1. Файл створено: %s\n", orig_file);

    // 2. Копіювання файлу від імені root (через sudo)
    printf("2. Копіюємо файл до домашньої директорії користувача (від імені root)...\n");
    char command[512];
    snprintf(command, sizeof(command),
             "sudo cp %s %s && sudo chown nastia:nastia %s",
             orig_file, copy_file, copy_file);
    int status = system(command);
    if (status != 0) {
        fprintf(stderr, "Помилка копіювання файлу\n");
        return 1;
    }
    printf("   Файл скопійовано: %s\n", copy_file);

    // 3. Зміна скопійованого файлу звичайним користувачем
    printf("3. Спроба змінити файл як звичайний користувач...\n");
    fp = fopen(copy_file, "a");
    if (fp == NULL) {
        perror("   Не вдалося відкрити файл для запису");
    } else {
        fprintf(fp, "Цей рядок доданий звичайним користувачем.\n");
        fclose(fp);
        printf("   Запис успішний\n");
    }

    // 4. Спроба видалення файлу
    printf("4. Спроба видалити файл як звичайний користувач...\n");
    if (remove(copy_file) == 0) {
        printf("   Файл успішно видалено\n");
    } else {
        perror("   Помилка видалення файлу");
    }

    // Прибираємо оригінальний файл
    remove(orig_file);

    return 0;
}
