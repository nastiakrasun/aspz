#!/bin/bash

# 1. Компiляцiя та аналiз hello.c
# Демонструє базовий розмір файлу та сегментів до додавання масиву
gcc -o hello hello.c
ls -l hello
size hello

# 2. Компiляцiя та аналiз hello2.c
# Додаємо глобальний масив з 1000 елементів, що збільшує сегмент BSS
gcc -o hello2 hello2.c
ls -l hello2
size hello2

# 3. Компiляцiя та аналiз hello3.c
# Додаємо ініціалізований масив, що переміщає його в сегмент DATA і збільшує розмір сегменту DATA
gcc -o hello3 hello3.c
ls -l hello3
size hello3

# 4. Компiляцiя та аналiз hello4.c
# Додаємо локальні масиви (стек, BSS, DATA) та аналізуємо зміни розмірів
gcc -o hello4 hello4.c
ls -l hello4
size hello4

# 5. Налагоджувальна версія для hello5.c
# Включає налагоджувальну інформацію, що збільшує загальний розмір файлу
gcc -g -o hello5_debug hello5.c
ls -l hello5_debug
size hello5_debug

# 6. Оптимізована версія для hello6.c
# Компиляція з максимальними оптимізаціями, що зменшує розмір файлу
gcc -O3 -o hello6_opt hello6.c
ls -l hello6_opt
size hello6_opt
