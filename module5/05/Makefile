obj-m += netlink_k.o

all: netlink_k user

user: user.o
	gcc user.o -o user
	rm user.o

user.o: user.c
	gcc -c user.c

netlink_k:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	sudo insmod netlink_k.ko

clean:
	sudo rmmod netlink_k.ko
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm user