#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_THREAD 2
#define MIN_THREAD 0 

pthread_mutex_t lock_valid_file;

sem_t sem_write;

pthread_t t_ID[MAX_THREAD];

void *my_thread(void *arg)
{

}

void main()
{
    int i = 0;

    /*innitialize mutex and semaphore*/
    pthread_mutex_init(&lock_valid_file, NULL);
    sem_init(&sem_write, MIN_THREAD, MAX_THREAD - 1);

    for(i = 0; i < MAX_THREAD -1 ; i++)
        pthread_create(&t_ID[i], NULL, my_thread, NULL);

    for(i = 0; i < MAX_THREAD -1;i++)
        pthread_join(t_ID, NULL);

    /*del mutex, semaphore*/
    pthread_mutex_destroy(&lock_valid_file);
    sem_destroy(&sem_write);

    puts("Everything ok\n");


}