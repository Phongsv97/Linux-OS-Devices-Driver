#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#define FILE_PATH 	"./test.txt"
#define MAX_LEN 	1024

int counter = 0;
char buffer[MAX_LEN +1] = "";

void signal_writeFile(int signo)
{
	
}

int  main()
{
	system("gcc -o B B.c");

	int pid_a = 0, pid = 0;
	int fd = 0, numb_write = 0;
	signal(SIGUSR1, signal_writeFile);
	

	/*creat pid process a  to file*/
	fd = open(FILE_PATH, O_RDWR | O_APPEND);
	
	if(-1 == fd){
		perror("Open fail\n");
		printf("In A, main open failed, errno:%s\n",strerror(errno));
		return -1;
	}

	pid_a = getpid();
	memset(buffer, 0, MAX_LEN);
	sprintf(buffer,"\npid of process A : %d\n", pid_a);
	numb_write = write(fd, buffer, MAX_LEN);
	counter = numb_write;
	write(fd, &counter, 1);
	close(fd);

	
 	
	/*make new process*/
	/*make new process*/
        pid_a = fork();
        switch(pid_a){
                case -1:
                        perror("fork() error\n"); break;
                case 0 :
                        execl("./B", "B", (char *)0);
                        break;
                default:{
                        /*get pid process B*/
                        int pid_B = 0;
                        char *temp ;

                        FILE *pipe = popen("pidof B", "r");
                        if(pipe  == NULL){
                                perror("pipe open fail\n");
                                return -1;
                        }
                        char line[MAX_LEN] = "";
                        fgets(line, MAX_LEN, pipe);
                        temp = strtok(line, " ");
                        pid_B = atoi(temp);
                        pclose(pipe);

                        /*send signal */
                        sleep(2);
                        kill(pid_B, SIGUSR2);

                        while(1);
                        break;
                }
        }

	return 0;
}	
