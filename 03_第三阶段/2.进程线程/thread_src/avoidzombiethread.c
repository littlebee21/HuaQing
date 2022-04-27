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


	sleep(1);	
	ret = pthread_join(tid,NULL);
	printf("pthread_join return val %d\n",ret);

	return 0;
}

void *entrance(void *arg)
{
	pthread_detach(pthread_self());//让线程成为分离的线程，该线程退出后由系统自动进行善后，对这样的线程调用pthread_join会失败
	printf("New thread exit\n");

	return NULL;
}
