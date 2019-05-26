#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sig_handler(int signo)
{
	if(12 == signo){
		/*do something*/
	}
}

void main()
{
	
	signal(12, sig_handler);
	printf("hello\n");

	sleep(10000000);
	printf("my pid : %d, im wakeup\n", getpid());
}
