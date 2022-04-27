#include <stdio.h>

#define N 8

int main()
{
	int arr[N] = {6,9,12,8,4,5,3,21};
	int cnt = N;
	int i = 0;
	int loc = 0;

	printf("Before delete:\n");
	for(i = 0;i < cnt;i++)
	{
		printf("%d ",arr[i]);
	}
	putchar('\n');

	printf("Please input a location[0,%d]:\n",N-1);
	scanf("%d",&loc);

	if(loc < 0 || loc >= N)
	{
		printf("Your input location is invalid\n");
		return 1;
	}

	for(i = loc + 1;i < N;i++)
	{
		arr[i-1] = arr[i];
	}
	cnt--;

	printf("After delete [3]:\n");
	for(i = 0;i < cnt;i++)
	{
		printf("%d ",arr[i]);
	}
	putchar('\n');

	return 0;
}
