CC = gcc

all: build

build: main

main: main.o queue.o
	$(CC) main.o queue.o -o main
	rm *.o

main.o: main.c queue.h
	$(CC) -c main.c

queue.o: queue.c queue.h
	$(CC) -c queue.c

clean:
	rm main