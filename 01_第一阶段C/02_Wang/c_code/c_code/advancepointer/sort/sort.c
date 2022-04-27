#include "mysort.h"

/*
 * 需解决的问题即元素类型不一样带来的问题
 * 1. 元素的sizeof是变化---- 交换时临时空间怎么来
 * 2. 元素比较大小的方法不一样-----某类函数进行统一   int compare(void *,void *)
 * 3. 元素类型可变无法用赋值 ------ memcpy
 * 4. 如果计算指定下标元素所在空间的首地址
 * */
int bubble_sort(void *pv,int cnt,int size,int (*pfcmp)(void *,void *))
{
	int i = 0;
	int j = 0;
	void *pt =NULL;
	char *pstart = (char *)pv;

	//动态分配用于交换的临时空间
	pt = malloc(size);
	if(NULL == pt)
	{
		printf("Malloc failed in %s at %d\n",__FILE__,__LINE__);
		return -1;
	}

	for(i = 0;i < cnt;i++)
	{
		for(j = 0;j < cnt - i - 1;j++)
		{
			if(pfcmp(pstart + j * size,pstart + (j+1) * size) > 0 )
			{
				memcpy(pt,pstart + j * size,size);
				memcpy(pstart + j * size,pstart + (j+1) *size,size);
				memcpy(pstart + (j+1) *size,pt,size);
			}
		}
	}

	//释放用于交换的临时空间
	free(pt);
	pt = NULL;

	return 0;
}

int select_sort(void *pv,int cnt,int size,int (*pfcmp)(void *,void *))
{
	int i = 0;
	int j = 0;
	int min = 0;
	void *pt =NULL;
	char *pstart = (char *)pv;

	//动态分配用于交换的临时空间
	pt = malloc(size);
	if(NULL == pt)
	{
		printf("Malloc failed in %s at %d\n",__FILE__,__LINE__);
		return -1;
	}

	for(i = 0;i < cnt;i++)
	{
		min = i;

		for(j = i + 1;j < cnt;j++)
		{
			if(pfcmp(pstart + j * size,pstart + min *size) < 0)
			{
				min = j;
			}
		}

		if(min != i)
		{
			memcpy(pt,pstart + min * size,size);
			memcpy(pstart + min * size,pstart + i * size,size);
			memcpy(pstart + i * size,pt,size);
		}
	}
	
	//释放用于交换的临时空间
	free(pt);
	pt = NULL;
	return 0;
}

int insert_sort(void *pv,int cnt,int size,int (*pfcmp)(void *,void *))
{
	int i = 0;
	int j = 0;
	void *pt =NULL;
	char *pstart = (char *)pv;

	//动态分配用于交换的临时空间
	pt = malloc(size);
	if(NULL == pt)
	{
		printf("Malloc failed in %s at %d\n",__FILE__,__LINE__);
		return -1;
	}

	for(i = 1;i < cnt;i++)
	{
		memcpy(pt,pstart + i * size,size);
		for(j = i -1;j >= 0;j--)
		{
			if(pfcmp(pstart + j * size,pt) > 0)
			{
				memcpy(pstart + (j+1) * size,pstart + j * size,size);
			}
			else
			{
				break;
			}
		}
		memcpy(pstart + (j+1) * size,pt,size);
	}

	
	//释放用于交换的临时空间
	free(pt);
	pt = NULL;
	return 0;
}
