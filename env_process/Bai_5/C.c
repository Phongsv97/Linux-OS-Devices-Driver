#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
        sleep(10);
        printf("id of C.c  %d\n" ,getpgid(0));
        return 0;
}

