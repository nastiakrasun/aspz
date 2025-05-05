#!/bin/bash

# Ім’я вихідного файлу C (можна змінити)
SRC_FILE="main.c"
# Ім’я виконуваного файлу
OUT_FILE="program"

# Компіляція
gcc -g "$SRC_FILE" -o "$OUT_FILE"

# Перевірка успіху
if [ $? -ne 0 ]; then
    echo "❌ Помилка компіляції!"
    exit 1
fi

# Запуск під Valgrind
valgrind --leak-check=full --track-origins=yes ./"$OUT_FILE"
