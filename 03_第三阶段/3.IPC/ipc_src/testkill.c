#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

#include <stdio.h>

int main(int argc,char *argv[])
{
	pid_t pid;
	int signo = 0;

	if(argc < 3)
	{
		printf("The argument is too few\n");
		return 1;
	}

	sscanf(argv[1],"%d",(int *)&pid);
	
	sscanf(argv[2],"%d",&signo);

	kill(pid,signo);

	return 0;
}
