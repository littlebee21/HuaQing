/*
 * 户输入整数n，创建新线程，在新线程中产生n个随机数，并排序，然后新线程退出后在主线程中输出排序后的n个数
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <time.h>

#include <pthread.h>

int input_number();
int print_arr(int *pi,int cnt);
void *rand_thread(void *arg);
int main(int argc,char *argv[])
{
	pthread_t tid;
	int ret = 0;
	int n = input_number();
	void *pret = NULL;

	srand(time(NULL));

	ret = pthread_create(&tid,NULL,rand_thread,(void *)(long)n);
	if(ret != 0)
	{
		printf("pthread_create failed\n");
		return 1;
	}

	pthread_join(tid,&pret);
	if(pret != NULL)
	{
		print_arr((int *)pret,n);
	}
	else
	{
		printf("create %d rand-number failed\n",n);
	}

	free(pret);
	pret = NULL;
	return 0;
}

int input_number()
{
	int x = 0;

	printf("Please input a number:\n");
	scanf("%d",&x);

	return x;
}

int print_arr(int *pi,int cnt)
{
	int i = 0;

	for(i = 0;i < cnt;i++)
	{
		printf("%d ",*(pi+i));
	}
	printf("\n");

	return 0;
}

int cmp_int(const void *pv1,const void *pv2);
void *rand_thread(void *arg)
{
	int n = (int)(long)arg;
	int *pi = NULL;
	int i = 0;

	pi = malloc(n * sizeof(int));
	if(NULL == pi)
	{
		printf("Malloc failed\n");
		return NULL;
	}
	memset(pi,0,n * sizeof(int));

	for(i = 0;i < n;i++)
	{
		*(pi + i) = rand() % 1000;
	}

	qsort(pi,n,sizeof(int),cmp_int);

	return pi;
}

int cmp_int(const void *pv1,const void *pv2)
{
	return *(int *)pv1 - *(int *)pv2;
}
