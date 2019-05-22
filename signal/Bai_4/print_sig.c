#include <stdio.h>
#include <signal.h>

int main()
{
    printf("%d\n", SIGRTMAX);
    int i = 0;
    sigset_t set, oldset;

    sigfillset(&set);
    sigdelset(&set,SIGINT);

    for (i = 0; i < NSIG; i++){
        if(sigismember(&set,i)){
            printf("signo : %d\n",i);
        }
    }
}

