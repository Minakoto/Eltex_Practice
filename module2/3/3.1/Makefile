CC = gcc

all: build

build: chmod

chmod: chmod.o
	$(CC) chmod.o -o chmod -lm
	rm *.o

chmod.o: chmod.c chmod.h
	$(CC) -c chmod.c

clean:
	rm chmod