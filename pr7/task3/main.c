#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("Number of arguments: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = '%s'\n", i, argv[i]);
    }

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <word> <filename>\n", argv[0]);
        return 1;
    }

    const char *word = argv[1];
    const char *filename = argv[2];

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("fopen failed");
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, word)) {
            printf("%s", line);
        }
    }

    fclose(file);
    return 0;
}
