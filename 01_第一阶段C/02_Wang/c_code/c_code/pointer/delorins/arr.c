#include <stdio.h>
int search_number(int *parr,int cnt,int n)
{
	int *pi = NULL;

	for(pi = parr;pi < parr + cnt;pi++)
	{
		if(*pi == n)
		{
			break;
		}
	}

	if(pi == parr + cnt)
	{
		return -1;
	}
	else
	{
		return pi - parr;
	}
}

//cnt为整个数组的大小，而不是有效元素的个数
//返回值：返回0插入成功，失败-1
int insert_number(int *parr,int cnt,int n) 
{
	int *pi = NULL;

	for(pi = parr + cnt - 2;pi >= parr;pi--)
	{
		if(*pi > n)
		{
			*(pi+1) = *pi;
		}
		else
		{
			break;
		}
	}
	*(pi + 1) = n;

	return 0;
}

int delete_number(int *parr,int cnt,int l) 
{
	int *pi = NULL;

	if(l < 0 || l >= cnt)
	{
		printf("The loc of delete is invalid\n");
		return -1;
	}

	for(pi = parr + l + 1;pi < parr+cnt;pi++)
	{
		*(pi - 1) = *pi;
	}

	return 0;
}

int print_array(int *parr,int cnt)
{
	int *pi = NULL;

	for(pi = parr;pi < parr + cnt;pi++)
	{
		printf("%d ",*pi);
	}
	putchar('\n');

	return 0;
}
