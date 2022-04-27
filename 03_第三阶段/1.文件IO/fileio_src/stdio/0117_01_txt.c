/*
 * 练习1：程序产生100个1000以内的随机数，将它们先保存到文件rand1.txt 中，然后从rand1.txt文件中读出这些数，对它们从小到大排序后再保存到文件rand2.txt中
 * */
#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#define N 100

#define DAT_FILE1 "./rand1.txt"
#define DAT_FILE2 "./rand2.txt"

int intcmp(const void *pv1,const void *pv2);
int main(int argc,char *argv[])
{
	int arr[N] = {0};
	int i = 0;
	FILE *pf1 = NULL;
	FILE *pf2 = NULL;
	int ret = 0;
	int buf[N] = {0};

	srand(time(NULL));

	for(i = 0; i < N;i++)
	{
		arr[i] = rand() % 1000;
	}

	pf1 = fopen(DAT_FILE1,"w+");
	if(NULL == pf1)
	{
		printf("fopen %s failed\n",DAT_FILE1);
		return 1;
	}

	for(i = 0;i < N;i++)
	{
		ret = fprintf(pf1,"%d ",arr[i]);
		if(ret <= 0)
		{
			break;
		}
	}
	if(ret <= 0)
	{
		fclose(pf1);
		pf1 = NULL;
		return 2;
	}

	fseek(pf1,0,SEEK_SET);

	for(i = 0;i < N;i++)
	{
		ret = fscanf(pf1,"%d",buf+i);
		if(ret != 1)
		{
			break;
		}
	}
	if(ret != 1)
	{
		fclose(pf1);
		pf1 = NULL;
		return 3;
	}

	fclose(pf1);
	pf1 = NULL;

	qsort(buf,N,sizeof(int),intcmp);


	pf2 = fopen(DAT_FILE2,"w");
	if(NULL == pf2)
	{
		printf("fopen %s failed\n",DAT_FILE2);
		return 4;
	}

	for(i = 0;i < N;i++)
	{
		ret = fprintf(pf2,"%d ",buf[i]);
		if(ret <= 0)
		{
			break;
		}
	}
	fclose(pf2);
	pf2 = NULL;
	if(ret <= 0)
	{
		return 2;
	}


	return 0;
}

int intcmp(const void *pv1,const void *pv2)
{
	return *(int *)pv1 - *(int *)pv2;
}
