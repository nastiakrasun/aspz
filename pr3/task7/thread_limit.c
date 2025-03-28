#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Функція для створення потоку
void* threadFunction(void* arg) {
    // Просто затримка для імітації роботи потоку
    while (1) {
        // Потік нічого не робить, просто працює в нескінченному циклі
    }
    return NULL;
}

int main() {
    pthread_t thread_id;
    int thread_count = 0;
    int max_threads = 10000;  // Встановіть максимальну кількість потоків, яку хочете створити

    printf("Starting to create threads...\n");

    // Створюємо потоки
    while (thread_count < max_threads) {
        if (pthread_create(&thread_id, NULL, threadFunction, NULL) != 0) {
            printf("Error creating thread %d\n", thread_count);
            break;
        }
        thread_count++;
    }

    printf("Created %d threads\n", thread_count);

    // Чекаємо натискання клавіші, щоб програма не завершилася відразу
    getchar();
    return 0;
}
