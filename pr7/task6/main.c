#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_DIRS 1024

int is_directory(const char *name) {
    struct stat st;
    if (stat(name, &st) == 0 && S_ISDIR(st.st_mode)) return 1;
    return 0;
}

int main() {
    DIR *d;
    struct dirent *entry;
    char *dirs[MAX_DIRS];
    int count = 0;

    d = opendir(".");
    if (!d) {
        perror("opendir failed");
        return 1;
    }

    while ((entry = readdir(d)) != NULL) {
        if (entry->d_name[0] == '.') continue;
        if (is_directory(entry->d_name)) {
            dirs[count] = strdup(entry->d_name);
            count++;
        }
    }
    closedir(d);

    qsort(dirs, count, sizeof(char *), (int (*)(const void *, const void *)) strcmp);

    for (int i = 0; i < count; i++) {
        printf("%s\n", dirs[i]);
        free(dirs[i]);
    }

    return 0;
}
