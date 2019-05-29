
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define DEVICE_NODE "/dev/vchar_dev"

#define LED_ON      '1'
#define LED_OFF     '0'

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
    char option = 'q';
    int fd = -1;

    printf("Select below options:\n");
    printf("\t1 (to open a device node : LED on )\n");
    printf("\t0 (to open a device node : LED off )\n");
    printf("\tc (to close the device node)\n");
    printf("\tq (to quit the application)\n");
    while (1) {
        printf("Enter your option: ");
        scanf(" %c", &option);

        switch (option) {
            case '1':
                if (fd < 0)
                    fd = open_chardev();
                else {
                    printf("%s has already opened\n", DEVICE_NODE);
                    write(fd, LED_ON, 1);
                }
                break;
            case '0':
                if (fd < 0)
                    fd = open_chardev();
                else {
                    printf("%s has already opened\n", DEVICE_NODE);
                    write(fd, LED_OFF, 1);
                }
                break;
            case 'c':
                if (fd > -1)
                    close_chardev(fd);
                else
                    printf("%s has not opened yet! Can not close\n", DEVICE_NODE);
                fd = -1;
                break;
            case 'q':
                if (fd > -1)
                    close_chardev(fd);
                printf("Quit the application. Good bye!\n");
                return 0;
            default:
                printf("invalid option %c\n", option);
                break;
        }
    };
}