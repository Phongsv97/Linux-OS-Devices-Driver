#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>

#define MM_SIZE 1024

int main()
{
    /*get key*/
    key_t key = ftok("./test", 65);
    if(key < 0){
        perror("ERROR create key error\n");
        exit(-1);
    }

    /*alloc memory from key*/
    int shmid = shmget(key, MM_SIZE, 0666 | IPC_CREAT);

    /*map shm*/
    char *str = (char *)shmat(shmid, (char *)0, 0);
        printf("write message to share memory : "); 
        fgets(str, 1024, stdin);
    

    /*un map*/
    shmdt(str);

    /*destroy*/
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}