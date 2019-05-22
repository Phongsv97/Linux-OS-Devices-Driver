#include <stdio.h>
#include <unistd.h>

void main()
{
	printf("session id of A : %d", getsid(0));
}
