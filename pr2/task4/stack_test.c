#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define MSG "In function %20s; &localvar = %p\n"

void handler(int signum) {
    printf("\nReceived signal %d, exiting...\n", signum);
    exit(EXIT_SUCCESS);
}

static void deep_function(void) {
    int localvar = 42;
    printf(MSG, __FUNCTION__, &localvar);
    printf("\nNow blocking on pause()...\n");
    pause();  // Блокує процес, чекаючи сигналу
}

static void middle_function(void) {
    int localvar = 21;
    printf(MSG, __FUNCTION__, &localvar);
    deep_function();
}

static void top_function(void) {
    int localvar = 10;
    printf(MSG, __FUNCTION__, &localvar);
    middle_function();
}

int main() {
    signal(SIGINT, handler);  // Обробка Ctrl+C (SIGINT)
    int localvar = 5;
    printf(MSG, __FUNCTION__, &localvar);
    top_function();
    return 0;
}
