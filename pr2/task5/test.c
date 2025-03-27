#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;

void bar() {
    printf("bar() почав виконання\n");
    longjmp(buf, 1);  // Спроба повернутися назад через зміну стека
    printf("bar() завершує виконання\n"); // Цей код не виконається!
}

void foo() {
    printf("foo() викликає bar()\n");
    bar();
    printf("foo() завершує виконання\n"); // Цей код також не виконається!
}

int main() {
    if (setjmp(buf) == 0) {
        printf("main() викликає foo()\n");
        foo();
    } else {
        printf("Повернення в main() через longjmp!\n");
    }
    printf("main() завершує виконання\n");
    return 0;
}
