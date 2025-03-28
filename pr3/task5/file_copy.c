#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_SIZE 10485760  // Максимальний розмір файлу (10 МБ)

// Функція для перевірки розміру файлу
long get_file_size(FILE *file) {
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Program need two arguments\n");
        return 1;
    }

    FILE *source = fopen(argv[1], "rb");
    if (!source) {
        printf("Cannot open file %s for reading\n", argv[1]);
        return 1;
    }

    FILE *destination = fopen(argv[2], "wb");
    if (!destination) {
        printf("Cannot open file %s for writing\n", argv[2]);
        fclose(source);
        return 1;
    }

    // Перевірка розміру першого файлу
    long source_size = get_file_size(source);
    if (source_size > MAX_FILE_SIZE) {
        printf("File size exceeds the limit\n");
        fclose(source);
        fclose(destination);
        return 1;
    }

    // Копіювання файлу
    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        if (fwrite(buffer, 1, bytes_read, destination) != bytes_read) {
            printf("Error writing to file %s\n", argv[2]);
            fclose(source);
            fclose(destination);
            return 1;
        }
    }

    printf("File copied successfully\n");

    fclose(source);
    fclose(destination);
    return 0;
}
