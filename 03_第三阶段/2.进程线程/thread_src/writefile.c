#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#define FILE_NAME "./test.txt"
void * new_thread(void *arg);
int main(int argc,char *argv[])
{
	pthread_t tid;
	int ret = 0;
	FILE *fp = NULL;
	int i = 0;
	void *pret = NULL;
	

	fp = fopen(FILE_NAME,"w");
	if(NULL == fp)
	{
		printf("a-fopen %s failed\n",FILE_NAME);
		return 1;
	}
	//ret = pthread_create(&tid,NULL,new_thread,"Hi!,New thread");
	ret = pthread_create(&tid,NULL,new_thread,(void *)fp);
	if(ret != 0)
	{
		printf("pthread_create failed,ret = %d\n",ret);
		return 1;
	}

	for(i = 0;i<5;i++)
	{
		fprintf(fp,"%s","abcdefgh");
	}

	//sleep(2);//做法不太准确
	pthread_join(tid,&pret);//准确做法
	printf("new thread return %ld\n",(long)pret);
	fclose(fp);
	fp = NULL;
	return 0;
}

void * new_thread(void *arg)
{
	int i = 0;

	for(i = 0;i<5;i++)
	{
		fprintf((FILE *)arg,"%s","12345678");
	}
	pthread_exit((void *)24);

	return (void *)23;//由于前面调用了pthread_exit,该句以及后续语句将不会被新线程执行
}

