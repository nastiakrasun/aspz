#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>

#define MIN_UID 1000  // змініть на 500 при потребі

int main() {
    FILE *fp;
    char line[1024];
    char *username;
    int uid;
    int found = 0;

    // Отримуємо поточного користувача
    uid_t current_uid = getuid();
    struct passwd *pw = getpwuid(current_uid);
    if (!pw) {
        perror("getpwuid");
        return 1;
    }
    char *current_user = pw->pw_name;
    printf("Поточний користувач: %s (UID: %d)\n", current_user, current_uid);

    // Виконуємо команду getent passwd
    fp = popen("getent passwd", "r");
    if (fp == NULL) {
        perror("popen");
        return 1;
    }

    // Читаємо кожен рядок (користувач)
    while (fgets(line, sizeof(line), fp)) {
        // Поділяємо рядок на поля
        char *fields[7];
        char *token = strtok(line, ":");
        int i = 0;
        while (token != NULL && i < 7) {
            fields[i++] = token;
            token = strtok(NULL, ":");
        }

        if (i < 3) continue; // UID має бути як мінімум третім полем

        username = fields[0];
        uid = atoi(fields[2]);

        // Перевіряємо чи це звичайний користувач, не root і не поточний
        if (uid >= MIN_UID && strcmp(username, current_user) != 0) {
            printf("Знайдено іншого звичайного користувача: %s (UID: %d)\n", username, uid);
            found = 1;
        }
    }

    pclose(fp);

    if (!found) {
        printf("Інших звичайних користувачів не знайдено.\n");
    }

    return 0;
}
