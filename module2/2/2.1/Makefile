CC = gcc

all: build

build: menu

menu: menu.o phonebook.o
	$(CC) menu.o phonebook.o -o menu
	rm *.o

menu.o: menu.c phonebook.h
	$(CC) -c menu.c

phonebook.o: phonebook.c phonebook.h
	$(CC) -c phonebook.c

clean:
	rm menu