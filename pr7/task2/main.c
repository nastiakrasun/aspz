#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_permissions(mode_t mode) {
    char perms[11] = "----------";
    if (S_ISDIR(mode)) perms[0] = 'd';
    if (S_ISLNK(mode)) perms[0] = 'l';

    perms[1] = (mode & S_IRUSR) ? 'r' : '-';
    perms[2] = (mode & S_IWUSR) ? 'w' : '-';
    perms[3] = (mode & S_IXUSR) ? 'x' : '-';
    perms[4] = (mode & S_IRGRP) ? 'r' : '-';
    perms[5] = (mode & S_IWGRP) ? 'w' : '-';
    perms[6] = (mode & S_IXGRP) ? 'x' : '-';
    perms[7] = (mode & S_IROTH) ? 'r' : '-';
    perms[8] = (mode & S_IWOTH) ? 'w' : '-';
    perms[9] = (mode & S_IXOTH) ? 'x' : '-';

    printf("%s ", perms);
}

int main() {
    DIR *d;
    struct dirent *dir;
    struct stat fileStat;

    d = opendir(".");
    if (!d) {
        perror("opendir failed");
        return 1;
    }

    while ((dir = readdir(d)) != NULL) {
        if (stat(dir->d_name, &fileStat) == -1) continue;

        print_permissions(fileStat.st_mode);
        printf("%ld ", fileStat.st_nlink);
        printf("%s ", getpwuid(fileStat.st_uid)->pw_name);
        printf("%s ", getgrgid(fileStat.st_gid)->gr_name);
        printf("%5ld ", fileStat.st_size);

        char timebuf[80];
        strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&fileStat.st_mtime));
        printf("%s ", timebuf);
        printf("%s\n", dir->d_name);
    }

    closedir(d);
    return 0;
}
