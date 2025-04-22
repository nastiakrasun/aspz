FROM ubuntu:22.04

# Встановлюємо необхідні пакунки без інтерактивного режиму
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    valgrind \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /usr/src/app

COPY . .

RUN gcc -g -o my_program main.c

CMD ["valgrind", "--leak-check=full", "./my_program"]

