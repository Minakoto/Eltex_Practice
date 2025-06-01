obj-m += chardev.o

all: main

main:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	sudo insmod chardev.ko

clean:
	sudo rmmod chardev.ko
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean