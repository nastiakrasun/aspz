#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float rand_float() {
    return (float)rand() / RAND_MAX;
}

float rand_float_range(float max) {
    return rand_float() * max;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <max_float>\n", argv[0]);
        return 1;
    }

    float n = atof(argv[1]);

    srand((unsigned int)time(NULL));

    printf("Random [0.0 - 1.0]: %f\n", rand_float());
    printf("Random [0.0 - %.2f]: %f\n", n, rand_float_range(n));

    return 0;
}
