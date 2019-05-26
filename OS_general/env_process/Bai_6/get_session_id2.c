#include <stdio.h>
#include <unistd.h>

void main()
{       
        printf("session id of B : %d", getsid(0));
} 
