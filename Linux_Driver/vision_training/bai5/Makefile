EXTRA_CFLAGS = -Wall

obj-m += _ioctl.o

all:
	make -C /lib/modules/`uname -r`/build 	M=`pwd` modules
	gcc -o app app.c
clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
	rm -rf app
