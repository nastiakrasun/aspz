#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file> <word>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return 1;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, argv[2])) {
            printf("%s", line);
        }
    }

    fclose(fp);
    return 0;
}
