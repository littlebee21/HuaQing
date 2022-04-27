#include <unistd.h>

#include <stdio.h>
#include <pthread.h>

void *entrance(void *arg);
int main(int argc,char *argv[])
{
	pthread_t tid;
	int ret = 0;

	ret = pthread_create(&tid,NULL,entrance,NULL);
	if(ret != 0)
	{
		printf("pthread_create Failed\n");
		return 1;
	}

	printf("my pid is %ld\n",(long)getpid());

	while(1)
	{
	}
	return 0;
}

void *entrance(void *arg)
{
	sleep(30);
	printf("New thread exit\n");

	return NULL;
}
