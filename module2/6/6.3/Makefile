CC = gcc
src := lib/add.c lib/sub.c lib/mul.c lib/div.c 
obj := add.o sub.o mul.o div.o 
files := lib/libadd.so lib/libsub.so lib/libmul.so lib/libdiv.so

all: build

build: menu

menu: menu.o $(files)
	$(CC) -rdynamic menu.o -o menu -ldl
	rm *.o

menu.o: menu.c calc.h
	$(CC) -c menu.c

calc.o: calc.c calc.h
	$(CC) -c calc.c

libs: $(libs) calc.h
	$(CC) -c -fPIC $(src)
	$(CC) -shared -o lib/libadd.so add.o
	$(CC) -shared -o lib/libsub.so sub.o
	$(CC) -shared -o lib/libmul.so mul.o
	$(CC) -shared -o lib/libdiv.so div.o
	rm *.o

clean:
	rm menu