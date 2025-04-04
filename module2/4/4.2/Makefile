CC = gcc

all: build

build: queue

queue: queue.o
	$(CC) queue.o -o queue
	rm *.o

queue.o: queue.c queue.h
	$(CC) -c queue.c