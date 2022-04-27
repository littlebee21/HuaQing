#include <stdio.h>

#define N 6
int main()
{
	int arr[N] = {0};
	int i = 0;
	int max = 0;
	int min = 0;

	/*数组输入*/
	printf("Please input %d number:\n",N);
	for(i = 0;i < N;i++)
	{
		scanf("%d",&arr[i]);
	}


	for(i = 1;i < N;i++)
	{
		if(arr[i] > arr[max])
		{
			max = i;
		}
		if(arr[i] < arr[min])
		{
			min = i;
		}
	}

	printf("The max number is %d,at %d\n",arr[max],max);
	
	/*for(i = 1;i < N;i++)
	{
		if(arr[i] < arr[min])
		{
			min = i;
		}
	}*/
	printf("The min number is %d,at %d\n",arr[min],min);
	return 0;
}
