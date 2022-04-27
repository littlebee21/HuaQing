#include <stdio.h>

#define N 8

int main()
{
	int arr[8] = {2,4,6,8,10,12,14,16};
	int num = 0;
	int low = 0;
	int high = 0;
	int mid = 0;

	printf("Please input a number:\n");
	scanf("%d",&num);

	low = 0;
	high = N - 1;
	
	while(low <= high)
	{
		//mid = (low+high)/2;
		mid = low + (num - arr[low]) * (high - low) / (arr[high]-arr[low]);
		if(arr[mid] > num)
		{
			high = mid - 1;
		}
		else if(arr[mid] < num)
		{
			low = mid + 1;
		}
		else
		{
			break;
		}
	}
	if(low > high)
	{
		printf("Not found\n");
	}
	else
	{
		printf("%d is at %d\n",num,mid);
	}

	return 0;
}
