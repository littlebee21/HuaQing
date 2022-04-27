#include <stdio.h>

#define N 4
#define M 4
int input_arr2d(int (*tarr)[M],int hs);
int get_sum_of_round(int (*tarr)[M],int hs);
int main()
{
	int arr[N][M] = {{0}};
	int sum = 0;

	input_arr2d(arr,N);

	sum = get_sum_of_round(arr,N);

	printf("The sum is %d\n",sum);

	return 0;
}

//int input_arr2d(int tarr[][M],int hs)
int input_arr2d(int (*tarr)[M],int hs)
{
	int i = 0;
	int (*parr)[M] = NULL;

	printf("Please input %d * %d numbers:\n",hs,M);
	for(parr = tarr;parr < tarr + hs;parr++)
	{
		for(i = 0;i < M;i++)
		{
			scanf("%d",*parr + i);
		}
	}

	return 0;
}

//int get_sum_of_round(int tarr[][M],int hs)
int get_sum_of_round(int (*tarr)[M],int hs)
{
	int i = 0;
	int sum = 0;
	int (*parr)[M] = NULL;

	printf("Please input %d * %d numbers:\n",hs,M);
	for(parr = tarr;parr < tarr + hs;parr++)
	{
		for(i = 0;i < M;i++)
		{
			if(parr == tarr || parr == tarr + hs - 1 || i == 0 || i == M -1)
			{
				sum += *(*parr + i);
			}
		}
	}

	return sum;
}
