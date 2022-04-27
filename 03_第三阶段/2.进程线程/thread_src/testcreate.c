#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

void * new_thread(void *arg);
int main(int argc,char *argv[])
{
	pthread_t tid;
	int ret = 0;
	//ret = pthread_create(&tid,NULL,new_thread,"Hi!,New thread");
	ret = pthread_create(&tid,NULL,new_thread,(void *)2022);
	if(ret != 0)
	{
		printf("pthread_create failed,ret = %d\n",ret);
		return 1;
	}
	while(1)
	{
		printf("Hi!Main Thead\n");
		sleep(1);
	}
	return 0;
}

void * new_thread(void *arg)
{
	while(1)
	{
		//printf("%s\n",(char *)arg);
		printf("%ld\n",(long)arg);
		
		sleep(1);
	}
	return (void *)23;
}

