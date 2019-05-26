#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define FILEPATH	"./test.txt"
#define MAX_READ	100
int main()
{
	int fd = -1;
	char buffer[MAX_READ +1];
	int numb_read = 0
		;
	fd = open(FILEPATH, O_RDONLY);
	if(-1 == fd)
	{
		perror("open fail");
		return -1;
	}

	//get content from file.
	numb_read = read(fd, buffer, MAX_READ);
	if(-1 == numb_read){
		perror("read fail");
	}
	buffer[numb_read] = '\0';
	close(fd);
                         
	puts(buffer);
	return 0;
}
