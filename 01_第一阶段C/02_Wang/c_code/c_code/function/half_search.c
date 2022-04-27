#include <stdio.h>

#define N 8

int half_search(int *pi,int low,int high,int key);
int main()
{
	int arr[N] = {2,4,6,8,10,12,14,16};
	int num = 0;
	int ret = 0;

	printf("Please input a number:\n");
	scanf("%d",&num);

	ret = half_search(arr,0,N-1,num);
	
	if(ret < 0)
	{
		printf("Not found\n");
	}
	else
	{
		printf("%d is at %d\n",num,ret);
	}

	return 0;
}

int half_search(int *pi,int low,int high,int key)
{
	int mid = 0;

	if(low > high)
	{
		return -1;
	}

	mid = (low + high) / 2;
	if(*(pi + mid) == key)
	{
		return mid;
	}
	else if(*(pi + mid) > key)
	{
		return half_search(pi,low,mid-1,key);
	}
	else
	{
		return half_search(pi,mid+1,high,key);
	}

}
