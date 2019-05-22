#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>


void main(int argc, char *argv[])
{
	int pid, status;

	pid = fork();
	switch(pid){
		case -1:
			perror("fork error\n"); break;
		case 0:
			if(-1 == execl("./child", "./child", (char *)0))
				perror("execl error\n");
			break;
		default:
			wait(&status);
			printf("status : %s\n", (status == 0) ? "ok" : "fail");
			break;
	}
}
