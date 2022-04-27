#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

struct rand
{
	int cnt;
	int *prands;
};

int insert_sort(int *pint,int num);
int delete(int *pint,int num,int loc);
int print_arr(int *pint,int num);
int main(int argc,char *argv[])
{
	struct rand myrands = {0};
	struct rand *pt = &myrands;
	int count = 0;
	int *pi = NULL;

	if(argc < 2)
	{
		printf("The argument is too few\n");
		return 1;
	}

	sscanf(argv[1],"%d",&count);
	if(count <= 0)
	{
		printf("The param is invalid\n");
		return 2;
	}

	//myrands.cnt = count;
	pt->cnt = count;

	srand(time(NULL));

	//myrands.prands = (int *)malloc(myrands.cnt * sizeof(int));
	pt->prands = (int *)malloc(pt->cnt * sizeof(int));
	//if(NULL == myrands.prands)
	if(NULL == pt->prands)
	{
		printf("Malloc failed\n");
		return 3;
	}
	//memset(myrands.prands,0,myrands.cnt * sizeof(int));
	memset(pt->prands,0,pt->cnt * sizeof(int));

	//for(pi = myrands.prands;pi < myrands.prands + myrands.cnt;pi++)
	for(pi = pt->prands;pi < pt->prands + pt->cnt;pi++)
	{
		*pi = rand() % 100;
	}

	//insert_sort(myrands.prands,myrands.cnt);
	insert_sort(pt->prands,pt->cnt);
	//myrands.cnt = delete(myrands.prands,myrands.cnt,0);
	pt->cnt = delete(pt->prands,pt->cnt,0);

	//print_arr(myrands.prands,myrands.cnt);
	print_arr(pt->prands,pt->cnt);

	//free(myrands.prands);
	free(pt->prands);
	//myrands.prands = NULL;
	pt->prands = NULL;
	return 0;
}

int print_arr(int *pint,int num)
{
	int *p = NULL;

	for(p = pint;p < pint + num;p++)
	{
		printf("%d ",*p);
	}
	putchar('\n');

	return 0;
}

int insert_sort(int *pint,int num)
{
	int i = 0;
	int j = 0;
	int t = 0;

	for(i = 1;i < num;i++)
	{
		t = *(pint + i);
		for(j = i-1;j >= 0;j--)
		{
			if(*(pint + j) > t)
			{
				*(pint + j + 1) = *(pint + j);
			}
			else
			{
				break;
			}
		}
		*(pint + j + 1) = t;
	}
	return 0;
}

int delete(int *pint,int num,int loc)
{
	int * p = NULL;

	if(loc < 0 || loc >= num)
	{
		printf("The param loc is invalid\n");
		return -1;
	}

	for(p = pint + loc + 1;p < pint + num;p++)
	{
		*(p-1) = *p;
	}

	return num-1;
}
