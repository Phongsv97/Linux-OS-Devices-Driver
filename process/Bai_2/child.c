#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FILE_PATH 	"./test.txt"


void main()
{
	char *buffer = "Hello world";
	int fd = -2, numWrite = 0;

	fd = open(FILE_PATH, O_WRONLY);
	if(-1 == fd){
		perror("open fail");
	}
	
	numWrite = write(fd, buffer, strlen(buffer));

	close(fd);
	
}
