#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define TEMP_FILE "tempfile.txt"

int main() {
    // 1. Створення файлу
    FILE *fp = fopen(TEMP_FILE, "w");
    if (!fp) {
        perror("Не вдалося створити файл");
        return 1;
    }
    fprintf(fp, "Це тимчасовий файл.\n");
    fclose(fp);
    printf("Файл %s створено.\n", TEMP_FILE);

    printf("\n==> Тепер запустіть ці команди вручну у терміналі від імені суперкористувача:\n");
    printf("   sudo chown root %s\n", TEMP_FILE);
    printf("   sudo chmod 600 %s\n", TEMP_FILE);
    printf("\nНатисніть Enter, коли зміни будуть внесені...\n");
    getchar();

    // 2. Перевірка прав доступу
    printf("==> Перевірка прав доступу як звичайний користувач:\n");

    // Спроба прочитати файл
    fp = fopen(TEMP_FILE, "r");
    if (!fp) {
        printf("Читання: Немає доступу (%s)\n", strerror(errno));
    } else {
        printf("Читання: Успішно\n");
        fclose(fp);
    }

    // Спроба записати у файл
    fp = fopen(TEMP_FILE, "a");
    if (!fp) {
        printf("Запис: Немає доступу (%s)\n", strerror(errno));
    } else {
        printf("Запис: Успішно\n");
        fprintf(fp, "Спроба запису...\n");
        fclose(fp);
    }

    return 0;
}
