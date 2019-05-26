#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    /* ftok to generate unique key - file*/
    key_t key = ftok("./test", 65);
    if(key < 0){
        perror("ERROR : create key errror occured\n");
        exit(-1);
    }

    /* alloc memory from key
    * shmget return an indentifier in shmid 
    * -share memory
    */
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    if(shmid < 0){
        perror("ERROR : create shmid error occured\n");
        exit(-1);
    }
    /* map shared memory to process address space.
    * shmat to attach to shared memory
    * return the address of the attached shared memory segment
    * arg 2 : 0 - read/write
    */
    char *str = (char *)shmat(shmid, (void *)0, 0);
    printf("read data from memory : ");
    while(strlen(str) == 0)
    {
        printf("%s\n",str);
    }
    

    /* umap shared memory in process addr space.
    * shmdt 
    */
    shmdt(str);

    /* destroy
    * IPC_RMID - destroy shm after use.
    */
    shmctl(shmid, IPC_RMID, NULL);

    return 0;

}