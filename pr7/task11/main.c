#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_FDS 20
#define MAX_VISITED 10000

typedef struct {
    dev_t dev;
    ino_t ino;
} inode_pair;

inode_pair visited[MAX_VISITED];
int visited_count = 0;

// Перевіряє, чи ми вже відвідали цей inode
int already_visited(dev_t dev, ino_t ino) {
    for (int i = 0; i < visited_count; i++) {
        if (visited[i].dev == dev && visited[i].ino == ino)
            return 1;
    }
    return 0;
}

// Додає inode до списку відвіданих
void add_visited(dev_t dev, ino_t ino) {
    if (visited_count < MAX_VISITED) {
        visited[visited_count].dev = dev;
        visited[visited_count].ino = ino;
        visited_count++;
    }
}

int print_tree(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
    // Уникаємо циклів
    if (typeflag == FTW_D || typeflag == FTW_DP) {
        if (already_visited(sb->st_dev, sb->st_ino)) {
            return 0; // вже відвідано
        } else {
            add_visited(sb->st_dev, sb->st_ino);
        }
    }

    for (int i = 0; i < ftwbuf->level; i++) {
        printf("  ");
    }

    if (typeflag == FTW_SL)
        printf("%s -> (symlink)\n", fpath + ftwbuf->base);
    else if (typeflag == FTW_D || typeflag == FTW_DP)
        printf("%s/\n", fpath + ftwbuf->base);
    else
        printf("%s\n", fpath + ftwbuf->base);

    return 0;
}

int main() {
    const char *start_path = "/";

    printf("Ієрархія директорій від кореня для користувача %s:\n\n", getenv("USER"));

    if (nftw(start_path, print_tree, MAX_FDS, FTW_PHYS) == -1) {
        perror("nftw");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
