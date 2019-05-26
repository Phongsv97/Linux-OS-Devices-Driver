#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define MAX_SIZE 1000

void main(int argc, char *argv[])
{
	char *filename;
	filename = argv[1];

	//open file.
	int fd;
	fd = open(filename, O_RDONLY);
	if(-1 == fd){
		perror("open fail \n");
	}

	//read contents from file.
	char buf[MAX_SIZE +1];
	int numb_read;
	numb_read = read(fd, buf, MAX_SIZE);
	if(-1 == numb_read){
		perror("read fail\n");
	}
	buf[numb_read] = '\0';

	//close file.
	close(fd);
	
	//display
	
	write(STDOUT_FILENO, buf, numb_read);
}
