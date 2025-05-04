#include <stdio.h>
#include <stdlib.h>

#define PAGE_LINES 20
#define MAX_LINE 1024

void wait_for_key() {
    printf("\n-- Press Enter to continue --");
    while (getchar() != '\n');
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> [file2 ...]\n", argv[0]);
        return 1;
    }

    for (int f = 1; f < argc; ++f) {
        FILE *fp = fopen(argv[f], "r");
        if (!fp) {
            perror("fopen failed");
            continue;
        }

        printf("==> %s <==\n", argv[f]);
        char line[MAX_LINE];
        int line_count = 0;

        while (fgets(line, sizeof(line), fp)) {
            printf("%s", line);
            if (++line_count >= PAGE_LINES) {
                wait_for_key();
                line_count = 0;
            }
        }

        fclose(fp);
    }

    return 0;
}
