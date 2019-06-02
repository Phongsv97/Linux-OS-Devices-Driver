#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define DEVICE_NODE "/dev/vchar_dev"

#define LED_OFF 0
#define LED_ON  1
#define CLOSE   2
#define QUIT    3
#define NKEYS   4

struct sym_struct {
    char *key;
    int val;
};

struct sym_struct lookup_table[] = {
    { "led_on", LED_ON }, { "led_off", LED_OFF}, { "close", CLOSE }, { "quit", QUIT}
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
    int fd = open(DEVICE_NODE, O_RDWR);
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
    printf("\tled_on    (to open a device node : LED on )\n");
    printf("\tled_off   (to open a device node : LED off )\n");
    printf("\tquit	(quit program)\n");
    while (1) {
        printf("Enter your option: ");
        gets(option);
        switch (keyfromstring(option)) {
            case LED_ON :
                fd = open_chardev();
                numb_write = write(fd, option, strlen(option));
                if(numb_write < 0)
                    printf("write failed\n");
		close(fd);
                break;
            case LED_OFF :
                fd = open_chardev();
                numb_write = write(fd, option, strlen(option));
                if(numb_write < 0)
                    printf("write failed\n");
		close(fd);
                break;
	    case QUIT :
		return 0;
	    default :
		printf("Invalid option \n");
        }
    };
}
