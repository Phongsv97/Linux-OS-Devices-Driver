#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN	100

void main(int argc, char* argv[])
{
	int i = 0,j = 0;
	char *buffer = (char *)malloc(sizeof(char)*MAX_LEN);

	for(i = 1;i < argc;i++){
		if(argv[i][0] == '-'){
			for(j = 1;j < strlen(argv[i]);j++){
				switch(argv[i][j]){
					case 'l' : strcat(buffer, "full property\n"); break;
					case 'a' : strcat(buffer, "hien thi file an\n"); break;
					default  : strcpy(buffer, "Incorrect flag\n"); break; 
				}
			}
		}
	}
	puts(buffer);
	free(buffer);
}
