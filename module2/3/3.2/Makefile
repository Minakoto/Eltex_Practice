CC = gcc

all: build

build: iptest

iptest: iptest.o
	$(CC) iptest.o -o iptest
	rm *.o

iptest.o: iptest.c
	$(CC) -c iptest.c

clean:
	rm iptest