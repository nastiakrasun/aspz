#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

void check_file(const char *path, const char *filename) {
    char fullpath[1024];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", path, filename);

    struct stat st;
    if (stat(fullpath, &st) == -1) {
        perror("stat");
        return;
    }

    printf("\nФайл: %s\n", fullpath);
    printf("Власник UID: %d, GID: %d\n", st.st_uid, st.st_gid);
    printf("Права: %o\n", st.st_mode & 0777);

    // Спроба читання
    int fd = open(fullpath, O_RDONLY);
    if (fd == -1) {
        printf("Читання: ❌ (%s)\n", strerror(errno));
    } else {
        printf("Читання: ✅\n");
        close(fd);
    }

    // Спроба запису
    fd = open(fullpath, O_WRONLY | O_APPEND);
    if (fd == -1) {
        printf("Запис: ❌ (%s)\n", strerror(errno));
    } else {
        printf("Запис: ✅\n");
        close(fd);
    }

    // Спроба виконання (тільки для /usr/bin)
    if (access(fullpath, X_OK) == 0) {
        printf("Виконання: ✅\n");
    } else {
        printf("Виконання: ❌ (%s)\n", strerror(errno));
    }
}

void scan_directory(const char *path, int limit) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return;
    }

    printf("\n>>> Каталог: %s\n", path);

    struct dirent *entry;
    int count = 0;
    while ((entry = readdir(dir)) != NULL && count < limit) {
        if (entry->d_type == DT_REG || entry->d_type == DT_LNK || entry->d_type == DT_UNKNOWN) {
            check_file(path, entry->d_name);
            count++;
        }
    }
    closedir(dir);
}

int main() {
    char *home = getenv("HOME");
    if (!home) {
        fprintf(stderr, "Не вдалося отримати домашній каталог\n");
        return 1;
    }

    // Перевірити файли в трьох каталогах
    scan_directory(home, 5);
    scan_directory("/usr/bin", 5);
    scan_directory("/etc", 5);

    return 0;
}
