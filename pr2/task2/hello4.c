#include <stdio.h>

void test() {
    int local_arr[1000]; // локальний масив у стеку
    static int static_arr[1000]; // у BSS
    static int static_arr_init[1000] = {1}; // у DATA
}

int main() {
    test();
    printf("Hello, World!\n");
    return 0;
}
