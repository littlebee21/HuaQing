/*
 *主线程接收用户输入，新线程负责输出，输入byebye退出程序
 */
#include <semaphore.h>
#include <stdio.h>
#include <string.h>

#include <pthread.h>

#define BUF_LEN 40

struct sharebuf
{
	char buf[BUF_LEN];
	sem_t sem;
};


int input_string(char *pout,int cnt);
void *print_thread(void *arg);
int main(int argc,char *argv[])
{
	pthread_t tid;
	int ret = 0;
	struct sharebuf shbuf = {""};

	sem_init(&shbuf.sem,0,0);

	ret = pthread_create(&tid,NULL,print_thread,&shbuf);
	if(ret != 0)
	{
		printf("pthread_create failed\n");
		return 1;
	}

	while(1)
	{
		input_string(shbuf.buf,BUF_LEN);
		sem_post(&shbuf.sem);
		if(strcmp(shbuf.buf,"byebye") == 0)
		{
			break;
		}
	}

	pthread_join(tid,NULL);
	sem_destroy(&shbuf.sem);
	return 0;
}

char *mygets(char *pout,int size);
int input_string(char *pout,int cnt)
{
	printf("Please input a string,input byebye will exit\n");
	mygets(pout,cnt);

	return 0;
}

void *print_thread(void *arg)
{
	struct sharebuf *pshbuf = (struct sharebuf *)arg;
	while(1)
	{
		sem_wait(&pshbuf->sem);
		if(strcmp(pshbuf->buf,"byebye") == 0)
		{
			break;
		}
		printf("The input string is %s\n",pshbuf->buf);
	}
	return NULL;
}
