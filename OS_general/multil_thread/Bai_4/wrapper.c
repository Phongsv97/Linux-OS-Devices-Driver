#include "my_print.h"

pthread_t tid;

void *my_thread_func(void *argc)
{
    print_name();
    pthread_exit(NULL);
}

void main()
{
    int ret;
    pthread_mutex_init(&lock, NULL);

    ret = pthread_create(&tid, NULL, my_thread_func, NULL);
    if(ret)
        printf("ERROR pthread_create() fail\n");
    pthread_join(tid, NULL);
}