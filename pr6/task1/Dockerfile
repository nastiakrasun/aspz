# Базовий образ із GCC
FROM gcc:latest

# Встановлення Valgrind
RUN apt-get update && apt-get install -y valgrind

# Директорія для нашого коду
WORKDIR /usr/src/app

# Копіюємо C-програму в контейнер
COPY main.c .

# Компілюємо C-програму
RUN gcc -g -o a.out main.c

# Команда за замовчуванням – перевірка Valgrind і запуск програми з ним
CMD valgrind --version && valgrind ./a.out
