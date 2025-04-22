# Вказуємо базовий образ
FROM ubuntu:22.04

# Встановлюємо необхідні пакунки
RUN apt-get update && apt-get install -y \
    build-essential \
    valgrind \
    && apt-get clean

# Встановлюємо робочу директорію
WORKDIR /usr/src/app

# Копіюємо файли в контейнер (наприклад, main.c)
COPY . .

# Компілюємо програму
RUN gcc -g -o my_program main.c

# Запускаємо програму під Valgrind
CMD ["valgrind", "--leak-check=full", "./my_program"]
