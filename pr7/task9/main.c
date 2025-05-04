#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void sample_code() {
    long sum = 0;
    for (long i = 0; i < 10000000; ++i) {
        sum += i;
    }
    printf("Result: %ld\n", sum);
}

int main() {
    struct timeval start, end;
    gettimeofday(&start, NULL);

    sample_code();

    gettimeofday(&end, NULL);
    long milliseconds = (end.tv_sec - start.tv_sec) * 1000L +
                        (end.tv_usec - start.tv_usec) / 1000;
    printf("Execution time: %ld ms\n", milliseconds);
    return 0;
}
