#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void main(int argc, char **argv) 
{
	FILE *fp;
	char buff[255], ch;

	if(argc !=2) {
		printf("Syntax error : ./r_char [path to text file]\n");
		exit(0);
	}
	
	fp = fopen(argv[1], "w");
	fclose(fp);

	printf("Read characters from terminal\n");
	printf("__Press any key__ \n");
		
	do {
		fflush(stdin);
		scanf("%c", &ch);
	 	if(ch == 'x') {	
			if(-1 == execl("./w_char", argv[1], buff, (char *)0))
				printf("Error ! execl\n");
			exit(0);	
		}
		strncat(buff, &ch, sizeof(char));
		
	}while(1);
}





