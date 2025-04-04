CC = gcc

all: build

build: menu

menu: menu.o phonebook.o liblinked.so
	$(CC) menu.o phonebook.o -o menu -L../6.2 -llinked -Wl,-rpath,/home/linomary/Projects/Eltex_Practice/module2/6/6.2/
	rm *.o

menu.o: menu.c phonebook.h
	$(CC) -c menu.c

phonebook.o: phonebook.c phonebook.h
	$(CC) -c phonebook.c

list: list.c list.h
	$(CC) -c -fPIC list.c
	$(CC) -shared -o liblinked.so list.o
	rm *.o

clean:
	rm menu
	rm liblinked.so