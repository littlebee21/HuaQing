/*主线程定义一个整型数组，数组元素的值由用户输入，在新建线程中完成找最大元素，然后在主线程中显示出最大元素及其下标位置*/

#include <stdio.h>

#include <pthread.h>

#define N 10
int input_arr(int *parr,int cnt);
void * find_max(void *arg);

struct intarr
{
	int *pi;
	int cnt;
};

int main(int argc,char *argv[])
{
	pthread_t tid;
	int ret = 0;
	int arr[N] = {0};
	struct intarr st = {arr,N};
	void *pret = NULL;
	int max = 0;

	input_arr(arr,N);

	ret = pthread_create(&tid,NULL,find_max,&st);
	if(ret != 0)
	{
		printf("pthread_create failed\n");
		return 1;
	}

	pthread_join(tid,&pret);

	max = (int)(long)pret;

	printf("In main-thread,the max number is %d at %d\n",arr[max],max);
	return 0;
}

int input_arr(int *parr,int cnt)
{
	int *pi = NULL;

	printf("Please input %d numbers:\n",cnt);
	for(pi=parr;pi < parr + cnt;pi++)
	{
		scanf("%d",pi);
	}

	return 0;
}

void * find_max(void *arg)
{
	struct intarr *pst = (struct intarr *)arg;
	int max = 0;
	int i = 0;
	int *parr = pst->pi;
	int cnt = pst->cnt;

	for(i = 1;i < cnt;i++)
	{
		if(*(parr+i) > *(parr+max))
		{
			max = i;
		}
	}

	return (void *)(long)max;
}

