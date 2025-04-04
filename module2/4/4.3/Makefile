CC = gcc

all: build

build: menu

menu: menu.o phonebook.o tree
	$(CC) menu.o phonebook.o -o menu -L. tree.a
	rm *.o

menu.o: menu.c phonebook.h
	$(CC) -c menu.c

phonebook.o: phonebook.c phonebook.h
	$(CC) -c phonebook.c

tree: tree.o
	ar q tree.a tree.o


tree.o: tree.c tree.h
	$(CC) -c tree.c

clean:
	rm menu
	rm tree.a