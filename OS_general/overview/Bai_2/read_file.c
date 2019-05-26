#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_READ 30

void main()
{
	char *filepath = "/home/slayder/Desktop/File/Bai_2/file";
	//Open file.
	int fd;
	char buf[30];
	fd = open(filepath, O_RDWR);
	if(-1 == fd){
		perror("open fail");
	}

	//get contents from file.
	int numb_read;
	numb_read = read(fd, buf, MAX_READ);
	if(-1 == numb_read){
		perror("read fail");
	}
	printf("Input data is : %s, strlen = %d\n", buf, numb_read);
	
	//close file.
	close(fd);

}
