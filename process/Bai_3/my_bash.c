#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getCmd(char *line, char *cmd)
{
	int index = 0,i = 0;
	if(strlen(line) < 1){
		printf("eroor\n");
		return -1;
	}
	while(line[index] != '\0' && line[index] != '\0'){
		cmd[i++] = line[index++];
	}
	if(line[index] != '\"'){
		fprintf(stderr, "command error\n");
		return -2;
	}
	cmd[i] = '\0';
	return 0;
}


int getContents(char *line, char *contents)
{
	int index = 0, i = 0;
	while(line[index] != '\"')
		index ++;
	while(line[++index] != '\"'){
		contents[i++] = line[index];
	}
	contents[i] = '\0';
}


int processing(const char *file_name)
{
	FILE *fp = NULL;
	int i = 0;
	char c;
	char line[100];
	char cmd[20];
	char contents[100];
	int index = 0;

	//open file
	fp = fopen(file_name, "r");
	if(fp == NULL){
		printf("open fail\n");
		return -1;
	}

	while((c = fgetc(fp)) != EOF){
		if(c != '\n'){
			line[index] = '\0';
			if(line[0] != '#'){
				if(0 == getCmd(line, cmd)){
					if(strcmp(cmd, "echo")){
						if(-2 == getContents(line, contents)){
							return -1;	
						}
						puts(contents);			
					}
				}			
			}
			index = 0;
		}
		else{
			line[index++] = c;		
		}
	}
 	return 0;
}


void main(int argc, char* argv[])
{
	processing(argv[1]);
}
