#include <stdio.h>

int find_maxmin(int *parr,int cnt,int *pmax,int *pmin);
#define N 6
int main()
{
	int arr[N] = {0};
	int i = 0;
	int rmax = 0;
	int rmin = 0;

	/*数组输入*/
	printf("Please input %d number:\n",N);
	for(i = 0;i < N;i++)
	{
		scanf("%d",&arr[i]);
	}

	find_maxmin(arr,N,&rmax,&rmin);
	printf("The max number is %d,at %d\n",arr[rmax],rmax);
	printf("The min number is %d,at %d\n",arr[rmin],rmin);
	return 0;
}

int find_maxmin(int *parr,int cnt,int *pmax,int *pmin)
{
	int max = 0;
	int min = 0;
	int *pi = NULL;

	if(NULL == parr || cnt <= 0 || NULL == pmax || NULL == pmin)
	{
		printf("Input param is invalid\n");
		return -1;
	}
	
	for(pi = parr + 1;pi < parr+N;pi++)
	{
		if(*pi > *(parr+max))
		{
			max = pi - parr;
		}
		if(*pi < *(parr+min))
		{
			min = pi - parr;
		}
	}

	*pmax = max;
	*pmin = min;

	return 0;
}
