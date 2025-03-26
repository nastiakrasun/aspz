cmake_minimum_required(VERSION 3.10)
project(MyProgram C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O2 -Wall")

# Створення бібліотек (статичних і динамічних)
add_library(process1 STATIC process1.c)
add_library(process1_shared SHARED process1.c)

add_library(process STATIC process.c)
add_library(process_shared SHARED process.c)

# Створення виконуваного файлу
add_executable(my_program main.c input.c output.c)

# Лінкування бібліотек
target_link_libraries(my_program PRIVATE process1 process)
