#include <stdio.h>
#include <stdlib.h>

void main(int argc, char **argv)
{
	FILE *fp;
	if((fp = fopen(argv[0], "w")) == NULL) {
		printf("Error ! Open file %s has problem\n", argv[1]);
		exit(0);
	}
	fprintf(fp, "%s\n", argv[1]);
       	exit(0);
}
