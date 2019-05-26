#include <stdio.h>
#include <signal.h>

void sig_handler(int sig_numb)
{
	if(2 == sig_numb)
		puts("Hello world\n");
}

void main()
{
	signal(2, sig_handler);
	printf("%d",SIGINT);
	while(1)
	{
	};
}
