#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/resource.h>

#define MAX_CPU_TIME 2  // Максимальний час ЦП в секундах

// Функція для перевірки перевищення ліміту часу
void check_cpu_time() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    if (usage.ru_utime.tv_sec >= MAX_CPU_TIME) {
        printf("Час ЦП вичерпано. Програма зупинена.\n");
        exit(0);
    }
}

// Функція для генерації випадкових чисел
void generate_numbers(int *numbers, int count, int max) {
    int i, num;
    for (i = 0; i < count; i++) {
        while (1) {
            num = rand() % max + 1;
            int unique = 1;
            for (int j = 0; j < i; j++) {
                if (numbers[j] == num) {
                    unique = 0;
                    break;
                }
            }
            if (unique) {
                numbers[i] = num;
                break;
            }
        }
    }
}

int main() {
    srand(time(NULL));

    int lottery_49[7];  // Масив для чисел 1-49
    int lottery_36[6];  // Масив для чисел 1-36

    // Встановлюємо обмеження на час процесора
    struct rlimit rl;
    rl.rlim_cur = MAX_CPU_TIME;
    rl.rlim_max = MAX_CPU_TIME;
    setrlimit(RLIMIT_CPU, &rl);

    // Генерація чисел для лотереї
    while (1) {
        check_cpu_time();  // Перевірка ліміту часу

        generate_numbers(lottery_49, 7, 49);
        generate_numbers(lottery_36, 6, 36);

        // Виведення результатів
        printf("Лотерейні числа (1-49): ");
        for (int i = 0; i < 7; i++) {
            printf("%d ", lottery_49[i]);
        }
        printf("\n");

        printf("Лотерейні числа (1-36): ");
        for (int i = 0; i < 6; i++) {
            printf("%d ", lottery_36[i]);
        }
        printf("\n");

        break;
    }

    return 0;
}
