/*
 * 线程a负责向字符数组中输入10个字符｀a｀，线程b负责向同一字符数组中输入10个字符｀b｀，主线程等两个线程退出后打印该字符数组的内容，要求打印结果只能是“abababababababababab”或“babababababababababa”

 */
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#define N 20
struct sharebuf
{
	char buf[N+4];
	int loc;

	pthread_mutex_t lock;
};

void *set_a(void *arg);
void *set_b(void *arg);
int main(int argc,char *argv[])
{
	struct sharebuf shbuf = {""};

	pthread_t tid1;
	pthread_t tid2;
	int ret = 0;

	pthread_mutex_init(&shbuf.lock,NULL);

	ret = pthread_create(&tid1,NULL,set_a,&shbuf);
	if(ret != 0)
	{
		pthread_mutex_destroy(&shbuf.lock);
		printf("pthread_create set_a thread failed\n");
		return 1;
	}
	ret = pthread_create(&tid2,NULL,set_b,&shbuf);
	if(ret != 0)
	{
		pthread_mutex_destroy(&shbuf.lock);
		printf("pthread_create set_b thread failed\n");
		return 1;
	}

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	printf("In main thread,buf=%s\n",shbuf.buf);

	pthread_mutex_destroy(&shbuf.lock);
	return 0;
}

void *set_a(void *arg)
{
	struct sharebuf *pshbuf = (struct sharebuf *)arg;
	int times = 0;


	while(1)
	{
		pthread_mutex_lock(&pshbuf->lock);
		if(pshbuf->loc % 2 == 0)
		{
			pshbuf->buf[pshbuf->loc] = 'a';
			pshbuf->loc++;
			times++;
		}
		pthread_mutex_unlock(&pshbuf->lock);
		if(times == 10)
		{
			break;
		}
	}


	return NULL;
}

void *set_b(void *arg)
{
	struct sharebuf *pshbuf = (struct sharebuf *)arg;
	int times = 0;

	while(1)
	{
		pthread_mutex_lock(&pshbuf->lock);
		if(pshbuf->loc % 2 != 0)
		{
			pshbuf->buf[pshbuf->loc] = 'b';
			pshbuf->loc++;
			times++;
		}
		pthread_mutex_unlock(&pshbuf->lock);
		if(times == 10)
		{
			break;
		}
	}

	return NULL;
}
