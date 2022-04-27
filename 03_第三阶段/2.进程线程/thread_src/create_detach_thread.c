#include <unistd.h>

#include <stdio.h>
#include <pthread.h>

void *entrance(void *arg);
int main(int argc,char *argv[])
{
	pthread_t tid;
	pthread_attr_t attr;
	int ret = 0;

	pthread_attr_init(&attr);

	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);//PTHREAD_CREATE_JOINABLE 可联结的线程
	ret = pthread_create(&tid,&attr,entrance,NULL);
	pthread_attr_destroy(&attr);
	if(ret != 0)
	{
		printf("pthread_create Failed\n");
		return 1;
	}



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
