#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FILE_PATH       "./loop_pid.txt"
#define LEN_MAX         1024


void main()
{
        int pid = 0;
        char line[LEN_MAX] = "";
        char *temp = NULL;
        
        pid = fork();
        switch(pid){    
                case -1:
                        perror("cannot creat process\n"); break;
                case  0:
                        system("./loop"); break;
                default:
                        /*Get pid of process need wakeup*/
                        system("pidof loop > loop_pid.txt");
                        FILE *fp = fopen(FILE_PATH, "r");

                        if(fp == NULL)
                       	 	perror("open fail\n");

                        fgets(line, LEN_MAX, fp);
                        temp = strtok(line, " ");
                        pid = atoi(temp);
			printf("pid value : %d\n", pid);

                       	fclose(fp);
                        kill(pid, 12);

                        break;
        }


}
