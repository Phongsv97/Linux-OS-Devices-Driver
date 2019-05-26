#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define RWERWERWE	(S_IRWXU | S_IRWXG | S_IRWXO )

int main(int argc, char* argv[])
{
	
	char *buff1 = (char *)malloc(sizeof(char)*100);
	char *buff2 = (char *)malloc(sizeof(char)*100);
	char *buff3 = (char *)malloc(sizeof(char)*100);
	char *buff4 = (char *)malloc(sizeof(char)*100);
	
	if(argc != 2) {
		perror("incorrect fomat comment\n");
	}


	sprintf(buff1, "%s/%s", argv[1], "Test_folder");
	sprintf(buff2, "%s/%s", buff1, "Test_1");
	sprintf(buff3, "%s/%s", buff1, "efg");
	sprintf(buff4, "%s/%s", buff2, "abc");
	
	if(0 == mkdir(buff1, RWERWERWE & (~(S_IXUSR | S_IXGRP | S_IWOTH | S_IXOTH )) ) ) {
		printf("success : %s\n", buff1);
		if(0 == mkdir( buff2, (RWERWERWE &(~(S_IXUSR | S_IXGRP | S_IXOTH | S_IWOTH) )) )) {
			printf("success : %s\n", buff4);
			if(0 ==  creat( buff4, (S_IRUSR | S_IRGRP| S_IROTH))) {

				printf("success : %s\n", buff2);
			}
		}
		if(0 == mkdir( buff3, (RWERWERWE &(~(S_IXUSR | S_IXGRP| S_IXOTH|S_IWOTH) )))) {
			printf("success : %s\n", buff3);
		}
	}

	return 0;
}
