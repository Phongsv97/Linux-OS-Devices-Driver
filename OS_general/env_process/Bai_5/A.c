#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	sleep(10);
	printf("id of A.c  %d\n" ,getpgid(0));
	return 0;
}
