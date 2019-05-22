#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *my_thread_fun()
{
    printf("Hello thread\n");
    return NULL;
}

int main()
{
    pthread_t thread_id = -1;
    printf("before thread\n");
    pthread_create(&thread_id, NULL, my_thread_fun, NULL);
    pthread_join(thread_id, NULL);
    printf("after thread\n");
    exit(0);
}