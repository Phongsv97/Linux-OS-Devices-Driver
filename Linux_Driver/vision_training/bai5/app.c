#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>

#define MAGIC_NO    100
#define CMD1  _IOW(MAGIC_NO, 0, char*)
#define CMD2  _IOW(MAGIC_NO, 1, char*)

#define DEVICE_NODE "/dev/vchar_device"

#define IOCTL_CMD1 0
#define IOCTL_CMD2 1
#define QUIT	   2
#define NKEYS	   3

struct sym_struct {
    char *key;
    int val;
};

struct sym_struct lookup_table[] = {
    { "ioctl_cmd1\n", IOCTL_CMD1 }, { "ioctl_cmd2\n", IOCTL_CMD2 }, { "quit\n", QUIT }
};

int keyfromstring(char *key)
{
    int i = 0;
    for(i = 0; i < NKEYS; i++) {
       if(strcmp(lookup_table[i].key, key) == 0)
            return lookup_table[i].val; 
    }
    return -1;
}

/* open */
int open_chardev() {
    int fd = open(DEVICE_NODE, O_WRONLY);
    if(fd < 0) {
        printf("Can not open the device file\n");
        exit(1);
    }
    return fd;
}

/* close */
void close_chardev(int fd) {
    close(fd);
}

int main() {
    int ret = 0;
    char option[30];
    int fd = -1;
    int numb_read = 0, numb_write = 0;

    printf("Select below options:\n");
    printf("\tioctl_cmd1  (to printk IOCTL_CMD1)\n");
    printf("\tioctl_cmd2  (to printk IOCTL_CMD2)\n");
    printf("\tquit	  (quit program)\n");
    while (1) {
        printf("Enter your option: ");
	fflush(stdin);
        fgets(option, 30, stdin);
        switch (keyfromstring(option)) {
            case IOCTL_CMD1 :
                fd = open_chardev();
                ioctl(fd, CMD1);
	        close(fd);
                break;
            case IOCTL_CMD2 :
                fd = open_chardev();
                ioctl(fd, CMD2);
		close(fd);
                break;
	    case QUIT :
		return 0;
	    default :
		printf("Invalid option \n");
        }
    };
}

