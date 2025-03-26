# Makefile для збірки програми

CC = gcc
CFLAGS = -g -O2 -Wall
LDFLAGS = -L/usr/lib -L$(HOME)/mylibs
LDLIBS = -lprocess1 -lprocess

SRCS = main.c input.c output.c
OBJS = $(SRCS:.c=.o)

TARGET = my_program

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) libprocess1.a libprocess1.so libprocess.a libprocess.so

# Створення статичних та динамічних бібліотек
libprocess1.a: process1.o
	ar rcs libprocess1.a process1.o

libprocess1.so: process1.c
	$(CC) -shared -fPIC -o libprocess1.so process1.c

libprocess.a: process.o
	ar rcs libprocess.a process.o

libprocess.so: process.c
	$(CC) -shared -fPIC -o libprocess.so process.c

# Правила для створення .o файлів бібліотек
process1.o: process1.c
	$(CC) $(CFLAGS) -c -fPIC process1.c -o process1.o

process.o: process.c
	$(CC) $(CFLAGS) -c -fPIC process.c -o process.o
