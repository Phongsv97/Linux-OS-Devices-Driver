EXTRA_CFLAGS = -Wall

obj-m += r_Serial.o

all:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules
	gcc -o terminal app.c
clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
	rm -rf terminal
