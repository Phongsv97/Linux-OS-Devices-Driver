#include <stdio.h>
#include <stdlib.h>

void main()
{
	FILE *in, *out;
	float var;

	//Open file
	if((in = fopen("./f_numbers.txt", "r")) == NULL) {
		printf("Error - Open file f_numbers.txt has problem\n");
		exit(0);
	}
	
	if((out = fopen("./f_numbers.bin", "wb")) == NULL) {
		printf("Error - Open file f_numbers.bin has problem\n");
		exit(0);
	}

	//Processing
	while(fscanf(in, "%f", &var) == 1) {
		fwrite(&var , sizeof(float), 1, out);
	}
	
	fclose(out);
	if((out = fopen("./f_numbers.bin", "rb")) == NULL) {
		printf("Error - Open file f_numbers.bin has problem\n");
		exit(0);
	}

	while(fread(&var, sizeof(float), 1, out) == 1) {
		printf("%.3f ", var);
	}
 	printf("\n");

	//close
	fclose(in);
	fclose(out);



}

