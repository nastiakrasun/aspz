#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Функція для порівняння двох цілих чисел для qsort
int compare_ints(const void *a, const void *b) {
    int int_a = *(const int*)a;
    int int_b = *(const int*)b;
    return (int_a > int_b) - (int_a < int_b);
}

// Функція перевірки правильності сортування
int is_sorted(const int *arr, size_t n) {
    for (size_t i = 1; i < n; i++) {
        if (arr[i-1] > arr[i]) {
            return 0; // масив не відсортований
        }
    }
    return 1; // масив відсортований
}

// Функція створення випадкового масиву
void generate_random_array(int *arr, size_t n) {
    for (size_t i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
}

// Функція створення відсортованого масиву
void generate_sorted_array(int *arr, size_t n) {
    for (size_t i = 0; i < n; i++) {
        arr[i] = i;
    }
}

// Функція створення зворотнього масиву
void generate_reverse_sorted_array(int *arr, size_t n) {
    for (size_t i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

// Функція створення масиву з однаковими елементами
void generate_same_elements_array(int *arr, size_t n, int value) {
    for (size_t i = 0; i < n; i++) {
        arr[i] = value;
    }
}

// Функція тестування qsort на різних масивах
void test_qsort() {
    printf("Running tests...\n");

    int arr1[] = {1, 2, 3, 4, 5};
    qsort(arr1, 5, sizeof(int), compare_ints);
    printf("Test 1 (already sorted): %s\n", is_sorted(arr1, 5) ? "PASSED" : "FAILED");

    int arr2[] = {5, 4, 3, 2, 1};
    qsort(arr2, 5, sizeof(int), compare_ints);
    printf("Test 2 (reverse sorted): %s\n", is_sorted(arr2, 5) ? "PASSED" : "FAILED");

    int arr3[] = {3, 1, 2, 5, 4};
    qsort(arr3, 5, sizeof(int), compare_ints);
    printf("Test 3 (random order): %s\n", is_sorted(arr3, 5) ? "PASSED" : "FAILED");

    int arr4[] = {7, 7, 7, 7, 7};
    qsort(arr4, 5, sizeof(int), compare_ints);
    printf("Test 4 (same elements): %s\n", is_sorted(arr4, 5) ? "PASSED" : "FAILED");

    int arr5[] = {};
    qsort(arr5, 0, sizeof(int), compare_ints);
    printf("Test 5 (empty array): %s\n", is_sorted(arr5, 0) ? "PASSED" : "FAILED");

    int arr6[] = {42};
    qsort(arr6, 1, sizeof(int), compare_ints);
    printf("Test 6 (single element): %s\n", is_sorted(arr6, 1) ? "PASSED" : "FAILED");

    printf("All tests finished.\n\n");
}

// Функція для проведення експерименту
void experiment() {
    const size_t n = 100000; // Розмір масиву
    int *arr = malloc(n * sizeof(int));
    if (!arr) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    clock_t start, end;
    double cpu_time_used;

    printf("Running experiment...\n");

    // Випадковий масив
    generate_random_array(arr, n);
    start = clock();
    qsort(arr, n, sizeof(int), compare_ints);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Random array sorted in %.6f seconds\n", cpu_time_used);

    // Вже відсортований масив
    generate_sorted_array(arr, n);
    start = clock();
    qsort(arr, n, sizeof(int), compare_ints);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Sorted array sorted in %.6f seconds\n", cpu_time_used);

    // Зворотній масив
    generate_reverse_sorted_array(arr, n);
    start = clock();
    qsort(arr, n, sizeof(int), compare_ints);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Reverse sorted array sorted in %.6f seconds\n", cpu_time_used);

    // Масив з однаковими елементами
    generate_same_elements_array(arr, n, 12345);
    start = clock();
    qsort(arr, n, sizeof(int), compare_ints);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Same elements array sorted in %.6f seconds\n", cpu_time_used);

    free(arr);
}

int main() {
    srand(time(NULL));

    test_qsort();
    experiment();

    return 0;
}
