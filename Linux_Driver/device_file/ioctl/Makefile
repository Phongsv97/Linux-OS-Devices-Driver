obj-m += led_mod.o

all :
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
check:
	././checkpath.pl --no-tree -f $(src-file)
