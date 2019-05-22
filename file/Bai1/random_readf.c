#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h> 

#define MAX_SIZE 1024

void main(int argc, char *argv[])
{
	char buf[MAX_SIZE +1];
	if(argc != 3){
		printf("Need Enter type : ./a.out <Filepath> offset\n");
	}

	//open file
	int fd,offset;
	fd = open(argv[1], O_RDONLY);

	//read file begin offset .
	offset = (int)atoi(argv[2]);
	lseek(fd, offset , SEEK_SET);

	
	int numb_read;
	numb_read = read(fd, buf, MAX_SIZE);
	if(-1 == fd){
		perror("read fail\n");
	}
	buf[numb_read] = '\0';
	
	//close file
	close(fd);

	//display.
	write(STDOUT_FILENO, buf, numb_read);
	
	

}

