CC = gcc
CFLAGS = -Wall -Wextra -O3
TARGET = program

all: $(TARGET)

$(TARGET): main.o erf_module.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o erf_module.o -lm

main.o: main.c erf_module.h
	$(CC) $(CFLAGS) -c main.c

erf_module.o: erf_module.c erf_module.h
	$(CC) $(CFLAGS) -c erf_module.c

clean:
	rm -f $(TARGET) *.o

