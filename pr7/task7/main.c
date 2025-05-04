#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

int ends_with(const char *str, const char *suffix) {
    if (!str || !suffix) return 0;
    size_t lenstr = strlen(str), lensuffix = strlen(suffix);
    return lenstr >= lensuffix && strcmp(str + lenstr - lensuffix, suffix) == 0;
}

int is_executable(const struct stat *st) {
    return st->st_mode & S_IXUSR;
}

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat st;

    dir = opendir(".");
    if (!dir) {
        perror("opendir failed");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (!ends_with(entry->d_name, ".c")) continue;
        if (stat(entry->d_name, &st) == -1) continue;

        printf("Found C file: %s\n", entry->d_name);
        printf("Add read permission to others? [y/n]: ");
        char answer = getchar();
        getchar(); // consume newline
        if (answer == 'y' || answer == 'Y') {
            if (chmod(entry->d_name, st.st_mode | S_IROTH) == -1)
                perror("chmod failed");
            else
                printf("Permission updated.\n");
        }
    }

    closedir(dir);
    return 0;
}
