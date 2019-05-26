#include <stdio.h>
#include <unistd.h>

void main()
{
	int pid = -1;
	pid = fork();

	switch(pid){
		case -1:
			perror("fork error"); break;
		case 0:
			printf("Im child %d, my PID : %d\n", pid, getpid()); break;
		default:
			printf("Im parent %d, my PID : %d\n", pid, getpid()); break;
	}
}

