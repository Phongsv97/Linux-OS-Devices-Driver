#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void sig_handler(int sig_numb)
{
	if(2 == sig_numb) 
		exit(0);
}

void main(int argc, char **argv)
{
	FILE *fd;
	int fd_rd, fd_wr;
	char buff[50];
	
	if(argc != 3) {
		printf("Syntax error : ./terminal [/dev/vchar_device_super] [path to log file]\n");
		exit(0);
	}
	
	/* Creat log file */
	fd = fopen(argv[2], "w");
	fclose(fd);

	
	/* Open file */
	fd_rd = open(argv[1], O_RDONLY);
	if(fd_rd == -1) {
		printf("Open file %s has problem\n", argv[1]);
		exit(0);
	}
	
	fd_wr = open(argv[2], O_WRONLY);
	if(fd_wr == -1) {
		printf("Open file %s has problem\n", argv[2]);
		exit(0);
	}
		
	/* Register signal [SIGINT] */
	signal(2, sig_handler);
	while(1) {
		read(fd_rd, buff, 50);
		write(fd_wr, buff, strlen(buff));
		printf("%s", buff);
	};

	/* Close file */
	close(fd_rd);
	close(fd_wr);
	

}
