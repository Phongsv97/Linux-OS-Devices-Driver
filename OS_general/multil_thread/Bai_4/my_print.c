#include "my_print.h"


void print_name()
{
    pthread_mutex_lock(&lock);
    printf("my nam : LE TRONG PHONG\n");
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}