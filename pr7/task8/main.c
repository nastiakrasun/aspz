#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int confirm(const char *filename) {
    printf("Delete %s? [y/n]: ", filename);
    char c = getchar();
    getchar(); // consume newline
    return (c == 'y' || c == 'Y');
}

int main() {
    DIR *d;
    struct dirent *entry;

    d = opendir(".");
    if (!d) {
        perror("opendir failed");
        return 1;
    }

    while ((entry = readdir(d)) != NULL) {
        if (entry->d_name[0] == '.') continue;
        if (confirm(entry->d_name)) {
            if (remove(entry->d_name) == 0)
                printf("Deleted %s\n", entry->d_name);
            else
                perror("remove failed");
        }
    }

    closedir(d);
    return 0;
}
