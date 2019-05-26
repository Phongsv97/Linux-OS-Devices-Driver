#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void sig_handler(int signo)
{
	if(2 == signo){
		switch(signo){
			case 2:
				printf("Hello im SIGINT\n");
			default:
				return ;
		}
	}
}

void main()
{
	sigset_t set, oldset;
	
	signal(2, sig_handler);

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigprocmask(SIG_BLOCK, &set, &oldset);

	while(1){
		/*get status object set when signal loader on kernel */
		sigpending(&set);
		if(sigismember(&set, 2)){
			printf("SIGINT : pending\n");
			exit(0);
		}
	}
}

