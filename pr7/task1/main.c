#include <stdio.h>

int main() {
    FILE *fp;
    fp = popen("rwho", "r");

    if (fp == NULL) {
        perror("popen failed");
        return 1;
    }

    FILE *more = popen("more", "w");
    if (more == NULL) {
        perror("popen for more failed");
        pclose(fp);
        return 1;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp)) {
        fputs(buffer, more);
    }

    pclose(fp);
    pclose(more);
    return 0;
}
