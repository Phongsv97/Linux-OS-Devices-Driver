#include <stdio.h>
#include <pthread.h>
#include <string.h>

/*A normal example C funtion that ex thread use argument.*/

struct info
{
    char name[64];
    char address[100];

};

void *my_thread(void *args)
{
    struct info *obj = args;
    printf("my name : %s", obj->name);
    pthread_exit(NULL);
}

int main()
{
    struct info obj;
    strncpy(obj.name, "LE TRONG PHONG", sizeof("LE TRONG PHONG"));

    pthread_t thread_ID;
    int ret;

    ret = pthread_create(&thread_ID, NULL, my_thread, &obj);
    if(ret)
        printf("ERROR pthread_creat() error occured\n");
    pthread_join(thread_ID, NULL);
    return 0;
}