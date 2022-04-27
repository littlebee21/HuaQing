#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

int delete_min(int *pi,int cnt);
int delete_max(int *pi,int cnt);
int print_int_arr(int *pi,int cnt);

int *create_num_rand(int n);
int destroy_num_rand(int *pi);

int main(int argc,char *argv[])
{
	int num = 0;
	int *pnum = NULL;

	if(argc < 2)
	{
		printf("The argument is too few,Usage:./dmm 16:\n");
		return 1;
	}
	
	sscanf(argv[1],"%d",&num);
	
	srand(time(NULL));

	pnum = create_num_rand(num);

	printf("Before Delete:\n");
	print_int_arr(pnum,num);

	num = delete_min(pnum,num);
	num = delete_min(pnum,num);
	num = delete_max(pnum,num);
	num = delete_max(pnum,num);
	
	printf("After Delete:\n");
	print_int_arr(pnum,num);
	
	destroy_num_rand(pnum);
	pnum = NULL;
	return 0;
}

int *create_num_rand(int n)
{
	int *pnum = NULL;
	int *pt = NULL;

	if(n <= 0)
	{
		printf("Input param is invalid\n");
		return NULL;
	}

	pnum = (int *)malloc(n * sizeof(int));
	if(NULL == pnum)
	{
		printf("Malloc failed\n");
		return NULL;
	}
	memset(pnum,0,n * sizeof(int));


	for(pt = pnum;pt < pnum + n;pt++)
	{
		*pt = rand() % 100;
	}

	return pnum;
}

int destroy_num_rand(int *pi)
{
	free(pi);
	pi = NULL;

	return 0;
}

int print_int_arr(int *pi,int cnt)
{
	int *p = pi;

	for(;p < pi + cnt;p++)
	{
		printf("%d ",*p);
	}
	putchar('\n');

	return 0;
}

int delete_max(int *pi,int cnt)
{
	int max = 0;
	int *p = NULL;

	for(p = pi + 1;p < pi + cnt;p++)
	{
		if(*p > *(pi + max))
		{
			max = p - pi;
		}
	}

	for(p = pi + max + 1;p < pi + cnt;p++)
	{
		*(p-1) = *p;
	}
	
	return cnt-1;
}

int delete_min(int *pi,int cnt)
{
	int min = 0;
	int *p = NULL;

	for(p = pi + 1;p < pi + cnt;p++)
	{
		if(*p < *(pi + min))
		{
			min = p - pi;
		}
	}

	for(p = pi + min + 1;p < pi + cnt;p++)
	{
		*(p-1) = *p;
	}
	
	return cnt-1;
}
