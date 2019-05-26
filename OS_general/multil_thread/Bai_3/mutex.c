#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREAD 2

pthread_t tid[MAX_THREAD];

pthread_mutex_t mutex;
int count;
void *my_thread(void *argvs)
{
    pthread_mutex_lock(&mutex);
    printf("thread %ld : %d\n",pthread_self(), count++ );
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main()
{
    int ret = 0;
    int i = 0;

    pthread_mutex_init(&mutex, NULL);

    for(i = 0; i < MAX_THREAD; i++){
        ret = pthread_create(&tid[i], NULL, my_thread, NULL);
        if(ret){
            perror("ERROR pthread_create fail\n");
            return -1;
        } 
        pthread_join(tid[i], NULL);
       
    }
    
    return 0;
}