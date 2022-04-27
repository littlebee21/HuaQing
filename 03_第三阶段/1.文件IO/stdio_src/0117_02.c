/*
 * 从上一题的rand2.dat文件中读出排序后的数，删除最小的10个数，输出剩余的均值，并将剩余数保存到文件rand3.dat
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DAT_FILE2 "./rand2.dat"
#define DAT_FILE3 "./rand3.dat"

float get_ave(int *pi,int cnt);
int main(int argc,char *argv[])
{
	int filelen = 0;
	FILE *pf2 = NULL;
	FILE *pf3 = NULL;
	int ret = 0;
	int *pi = NULL;
	int cnt = 0;

	pf2 = fopen(DAT_FILE2,"rb");
	if(NULL == pf2)
	{
		printf("fopen %s failed\n",DAT_FILE2);
		return 1;
	}

	fseek(pf2,0,SEEK_END);
	filelen = ftell(pf2);

	pi = (int *)malloc(filelen);
	if(NULL == pi)
	{
		printf("Malloc failed\n");
		fclose(pf2);
		pf2 = NULL;
		return 2;
	}
	memset(pi,0,filelen);

	cnt = filelen/sizeof(int);
	if(cnt <= 10)
	{
		printf("count of int-element is invalid,cnt = %d\n",cnt);
		free(pi);
		pi = NULL;
		fclose(pf2);
		pf2 = NULL;
		return 3;

	}

	fseek(pf2,0,SEEK_SET);
	ret = fread(pi,sizeof(int),cnt,pf2);
	fclose(pf2);
	pf2 = NULL;
	if(ret != cnt)
	{
		printf("fread %d * int into %s failed,ret=%d\n",cnt,DAT_FILE2,ret);
		free(pi);
		pi = NULL;
		return 4;
	}
	
	memmove(pi,pi+10,(cnt - 10) * sizeof(int));
	cnt-=10;

	printf("The ave is %.2f\n",get_ave(pi,cnt));




	pf3 = fopen(DAT_FILE3,"wb");
	if(NULL == pf3)
	{
		printf("fopen %s failed\n",DAT_FILE3);
		return 4;
	}


	ret = fwrite(pi,sizeof(int),cnt,pf3);
	fclose(pf3);
	pf3 = NULL;
	if(ret != cnt)
	{
		printf("fwrite %d * int into %s failed,ret=%d\n",cnt,DAT_FILE3,ret);
		return 5;
	}

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
