#include <stdio.h>
#include <unistd.h>

void main()
{       
        printf("session id of C : %d", getsid(0));
}
