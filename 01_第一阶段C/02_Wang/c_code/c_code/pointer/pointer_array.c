#include <stdio.h>

#define N 4

#define M 3

int get_sum(int *pi,int cnt);
int get_max_array(int *paddr[],int cnt);
int print_array(int *pi,int cnt);
int main()
{
	int arr1[N] = {1,2,3,4};
	int arr2[N] = {5,6,7,8};
	int arr3[N] = {3,4,5,6};
	
	int *addrarr[M] = {arr1,arr2,arr3};

	int ret = get_max_array(addrarr,M);

	print_array(addrarr[ret],N);
	
	return 0;
}

int print_array(int *pi,int cnt)
{
	int *p = NULL;

	for(p = pi;p < pi + cnt;p++)
	{
		printf("%d ",*p);
	}
	putchar('\n');
	return 0;
}

int get_max_array(int *paddr[],int cnt)
//int get_max_array(int** paddr,int cnt)
{
	int max = 0;
	/*	
	int i = 0;
	for(i = 1;i < cnt;i++)
	{
		if(get_sum(paddr[max],N) < get_sum(paddr[i],N))
		{
			max = i;
		}
	}
	*/
	int **pp = NULL;

	for(pp = paddr+1;pp < paddr + cnt;pp++)
	{
		if(get_sum(*pp,N) > get_sum(*(paddr+max),N))
		{
			max = pp - paddr;
		}
	}

	return max;
}

int get_sum(int *pi,int cnt)
{
	int sum = 0;
	int *p = NULL;

	for(p = pi;p < pi + cnt;p++)
	{
		sum += *p;
	}

	return sum;
}
