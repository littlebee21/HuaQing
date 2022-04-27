#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 8
int shell_sort(void *parr,int cnt,int size,int (*pf)(const void *,const void *));

int intcmp(const void *pv1,const void *pv2);
int main()
{
	int arr[N] = {85,32,66,73,52,46,27,12};
	int i = 0;

	shell_sort(arr,N,sizeof(int),intcmp);

	printf("After sort:\n");
	for(i = 0;i < N;i++)
	{
		printf("%d ",arr[i]);
	}
	putchar('\n');

	return 0;
}
int intcmp(const void *pv1,const void *pv2)
{
	return *(int *)pv1 - *(int *)pv2;
}

int shell_sort(void *parr,int cnt,int size,int (*pf)(const void *,const void *))
{
	int i = 0;//轮数
	int j = 0;//协助每轮在【0，N-1-i】间将最大元素通过多次的比较交换到下标N-i位置
	int gap = cnt / 2;
	char *pstart = (char *)parr;
	void *pt = NULL;

	pt = malloc(size);
	if(NULL == pt)
	{
		printf("Malloc Failed,%s:%d\n",__FILE__,__LINE__);
		return -1;
	}
	memset(pt,0,size);
	

	while(gap > 0)
	{
		for(i = gap;i < cnt;i++)
		{
			//1. arr[i] ---->  t
			memcpy(pt,pstart + i * size,size);
		
			//2. 将t插入在[0,i](i位为空位)，插入后确保[0,i]范围从小到大排序
			for(j=i-gap;j>=0;j-=gap)
			{
				if(pf(pstart + j * size,pt) > 0)
				{
					memcpy(pstart + (j+gap) * size,pstart + j * size,size);
				}
				else
				{
					break;
				}
			}
			memcpy(pstart + (j+gap) * size,pt,size);
		}

		gap = gap / 2;
	}

	free(pt);
	pt = NULL;
	return 0;
}
