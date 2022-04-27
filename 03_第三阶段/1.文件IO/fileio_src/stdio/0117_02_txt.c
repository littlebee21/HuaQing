/*
 * 从上一题的rand2.txt文件中读出排序后的数，删除最小的10个数，输出剩余的均值，并将剩余数保存到文件rand3.txt
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DAT_FILE2 "./rand2.txt"
#define DAT_FILE3 "./rand3.txt"

float get_ave(int *pi,int cnt);
int main(int argc,char *argv[])
{
	FILE *pf2 = NULL;
	FILE *pf3 = NULL;
	int ret = 0;
	int *pi = NULL;
	int cnt = 0;
	int temp = 0;
	int i = 0;

	pf2 = fopen(DAT_FILE2,"r");
	if(NULL == pf2)
	{
		printf("fopen %s failed\n",DAT_FILE2);
		return 1;
	}

	ret = fscanf(pf2,"%d",&temp);
	while(ret == 1)
	{
		cnt++;
		ret = fscanf(pf2,"%d",&temp);
	}

	pi = (int *)malloc(cnt * sizeof(int));
	if(NULL == pi)
	{
		printf("Malloc failed\n");
		fclose(pf2);
		pf2 = NULL;
		return 2;
	}
	memset(pi,0,cnt *sizeof(int));

	fseek(pf2,0,SEEK_SET);
	for(i = 0;i < cnt;i++)
	{
		fscanf(pf2,"%d",pi+i);
	}

	memmove(pi,pi+10,(cnt - 10) * sizeof(int));
	cnt-=10;

	printf("The ave is %.2f\n",get_ave(pi,cnt));


	pf3 = fopen(DAT_FILE3,"w");
	if(NULL == pf3)
	{
		printf("fopen %s failed\n",DAT_FILE3);
		return 4;
	}

	for(i = 0;i < cnt;i++)
	{
		ret = fprintf(pf3,"%d ",*(pi + i));
		if(ret <= 0)
		{
			break;
		}
	}
	if(ret <= 0)
	{
		return 5;
	}

	fclose(pf3);
	pf3 = NULL;

	free(pi);
	pi = NULL;
	return 0;
}

float get_ave(int *pi,int cnt)
{
	int i = 0;
	int sum = 0;

	for(i = 0;i < cnt;i++)
	{
		sum += *(pi + i);
	}

	return (float)sum/cnt;
}
