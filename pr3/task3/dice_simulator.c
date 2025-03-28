#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>

#define MAX_FILE_SIZE 1024  // Максимальний розмір файлу в байтах
#define FILE_NAME "dice_results.txt"

int get_file_size(const char *filename) {
    struct stat st;
    if (stat(filename, &st) == 0) {
        return st.st_size;
    }
    return 0;
}

int roll_dice() {
    return rand() % 6 + 1;
}

int main() {
    srand(time(NULL));
    FILE *file = fopen(FILE_NAME, "a");
    if (!file) {
        perror("Не вдалося відкрити файл");
        return 1;
    }
    
    while (get_file_size(FILE_NAME) < MAX_FILE_SIZE) {
        int result = roll_dice();
        fprintf(file, "%d\n", result);
        fflush(file);
    }
    
    printf("Досягнуто максимального розміру файлу. Запис припинено.\n");
    fclose(file);
    return 0;
}
