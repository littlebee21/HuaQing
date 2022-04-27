/*
 *线程1向一个字符数组中输入多个字符'a'，线程2向一个字符数组中输入多个字符'b'，主线程等两个线程退出后负责打印该字符数组的内容，要求打印的结果不能有ab字符同时出现
 */
#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#define N 20
struct sharebuf
{
	char buf[N+4];

	sem_t lock;
};

void *set_a(void *arg);
void *set_b(void *arg);
int main(int argc,char *argv[])
{
	struct sharebuf shbuf = {""};

	pthread_t tid1;
	pthread_t tid2;
	int ret = 0;

	sem_init(&shbuf.lock,0,1);

	ret = pthread_create(&tid1,NULL,set_a,&shbuf);
	if(ret != 0)
	{
		sem_destroy(&shbuf.lock);
		printf("pthread_create set_a thread failed\n");
		return 1;
	}
	ret = pthread_create(&tid2,NULL,set_b,&shbuf);
	if(ret != 0)
	{
		sem_destroy(&shbuf.lock);
		printf("pthread_create set_b thread failed\n");
		return 1;
	}

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	printf("In main thread,buf=%s\n",shbuf.buf);

	sem_destroy(&shbuf.lock);
	return 0;
}

void *set_a(void *arg)
{
	struct sharebuf *pshbuf = (struct sharebuf *)arg;
	int i = 0;

	sem_wait(&pshbuf->lock);
	for(i = 0;i < N;i++)
	{
		pshbuf->buf[i] = 'a';
		sleep(1);
	}
	sem_post(&pshbuf->lock);

	return NULL;
}

void *set_b(void *arg)
{
	struct sharebuf *pshbuf = (struct sharebuf *)arg;
	int i = 0;

	sem_wait(&pshbuf->lock);
	for(i = 0;i < N;i++)
	{
		pshbuf->buf[i] = 'b';
		sleep(1);
	}
	sem_post(&pshbuf->lock);

	return NULL;
}
