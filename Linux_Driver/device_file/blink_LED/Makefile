obj-m := char_led.o
src-file := char_led.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:

	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
check:
	././checkpatch.pl --no-tree -f $(src-file)
