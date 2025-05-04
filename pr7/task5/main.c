#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void list_files(const char *base_path) {
    DIR *dir = opendir(base_path);
    if (!dir) return;

    struct dirent *entry;
    char path[1024];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(path, sizeof(path), "%s/%s", base_path, entry->d_name);
        struct stat st;
        if (stat(path, &st) == -1) continue;

        printf("%s\n", path);
        if (S_ISDIR(st.st_mode)) {
            list_files(path);
        }
    }

    closedir(dir);
}

int main() {
    list_files(".");
    return 0;
}
