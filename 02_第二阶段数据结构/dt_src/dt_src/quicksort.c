#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 8
int quick_sort(void *parr,int cnt,int size,int (*pf)(const void *,const void *));
int intcmp(const void *pv1,const void *pv2);

#if 0
int quick_sort_int(int *parr,int low,int high);
#endif

int main()
{
	int arr[N] = {85,32,66,73,52,46,27,12};
	int i = 0;

	quick_sort(arr,N,sizeof(int),intcmp);

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

#if 0 
/*函数功能：以下标为low的元素值为基准值，将parr指向的数组，分为三个部分：
 *1. 左边部分全部比基准小
  2. 右边部分全部比基准大
  3. 中间一个元素位置存放基准值，函数返回该中间下标值
 * */
static int divide_array(int *parr,int low,int high)
{
	int t = *(parr + low);

	while(low < high)
	{
		/*下标从高到低找第一个比t小的元素的下标（high）*/
		while(low < high && *(parr + high) >= t)
		{
			high--;
		}
		*(parr+low) = *(parr + high);

		/*下标从低到高找第一个比t大的元素的下标（low）*/
		while(low < high && *(parr + low) <= t)
		{
			low++;
		}
		*(parr+high) = *(parr + low);
	}

	*(parr+low) = t;

	return low;
}

int quick_sort_int(int *parr,int low,int high)
{
	int mid = 0;

	if(low >= high)
	{
		return 0;
	}
	mid = divide_array(parr,low,high);
	quick_sort_int(parr,low,mid-1);
	quick_sort_int(parr,mid+1,high);
	return 0;
}
#endif

static int divide_array(void *parr,int low,int high,int size,void * pt,int (*pf)(const void *,const void *))
{
	char *pstart = (char *)parr;

	memcpy(pt,pstart + low * size,size);
	while(low < high)
	{
		while(low < high && pf(pstart + high * size,pt) >= 0)
		{
			high--;
		}
		memcpy(pstart + low * size,pstart + high *size,size);
		
		while(low < high && pf(pstart + low * size,pt) <= 0)
		{
			low++;
		}
		memcpy(pstart + high * size,pstart + low *size,size);
	}

	memcpy(pstart + low * size,pt,size);

	return low;
}

static int quick_sort_private(void *parr,int low,int high,int size,void * pt,int (*pf)(const void *,const void *))
{
	int mid = 0;

	if(low >= high)
	{
		return 0;
	}

	mid = divide_array(parr,low,high,size,pt,pf);
        quick_sort_private(parr,low,mid-1,size,pt,pf);
        quick_sort_private(parr,mid+1,high,size,pt,pf);
	return 0;
}

int quick_sort(void *parr,int cnt,int size,int (*pf)(const void *,const void *))
{
	void *pt = NULL;

	pt = malloc(size);
	if(NULL == pt)
	{
		printf("Malloc Failed,%s:%d\n",__FILE__,__LINE__);
		return -1;
	}
	memset(pt,0,size);

	quick_sort_private(parr,0,cnt-1,size,pt,pf);

	free(pt);
	pt = NULL;
	return 0;
}

