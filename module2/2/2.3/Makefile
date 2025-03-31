CC = gcc

all: build

build: menu

menu: menu.o calc.o
	$(CC) menu.o calc.o -o menu
	rm *.o

menu.o: menu.c calc.h
	$(CC) -c menu.c

calc.o: calc.c calc.h
	$(CC) -c calc.c

clean:
	rm menu