#include <signal.h>

#include <stdio.h>

void handler_2_sig(int signo);

int main(int argc,char *argv[])
{
	
	//signal(2,handler_2_sig);
	
	{
		struct sigaction newact;

		newact.sa_handler = handler_2_sig;
		newact.sa_flags = 0;
		sigemptyset(&newact.sa_mask);
		sigaction(2,&newact,NULL);
	}

	while(1)
	{
	}

	return 0;
}

void handler_2_sig(int signo)
{
	printf("Handling %d signal\n",signo);
}
