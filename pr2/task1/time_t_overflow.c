#include <stdio.h>
#include <time.h>
#include <stdint.h>

int main() {
    time_t max_time = (time_t)((uint64_t)-1 >> 1); // Максимальне значення для signed time_t
    printf("Максимальне значення time_t: %lld\n", (long long)max_time);
    printf("Дата та час максимального значення: %s", ctime(&max_time));

    return 0;
}

/* 
    Компільований виконуваний файл для 32-бітної архітектури:
    gcc -m32 time_t_overflow.c -o time_t_overflow_32 
*/

/* 
    Компільований виконуваний файл для 64-бітної архітектури:
    gcc -m64 time_t_overflow.c -o time_t_overflow_64 
*/
