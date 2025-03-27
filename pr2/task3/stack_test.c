#include <stdio.h>
#include <stdlib.h>

int global_var; // глобальна змінна (сегмент даних)
static int static_var; // статична змінна (сегмент даних)

int main() {
    int local_var; // локальна змінна (стек)
    int *heap_var = (int *)malloc(sizeof(int)); // змінна в купі

    printf("The stack top is near %p\n", &local_var);
    printf("Address of global variable: %p\n", &global_var);
    printf("Address of static variable: %p\n", &static_var);
    printf("Address of heap variable: %p\n", heap_var);

    // Збільшення розміру стека за допомогою великих масивів
    int large_array[10000];
    printf("The stack top after increasing stack size is near %p\n", &large_array);

    free(heap_var); // звільнення пам'яті купи
    return 0;
}
