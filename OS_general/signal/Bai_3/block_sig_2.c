#include <stdio.h>
#include <signal.h>

void signal_handler(int signo)
{
	if(2 == signo){
		switch(signo)
		{
			case 2:
				printf("Hello SIGINT\n"); break;
			default:
				printf("SIGINT not value : %d\n",signo); 
				break;
		}
	}
}

void main()
{
	signal(2 , signal_handler);

	sigset_t set, oldset;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigprocmask(SIG_UNBLOCK, &set, &oldset);
	while(1);
}
