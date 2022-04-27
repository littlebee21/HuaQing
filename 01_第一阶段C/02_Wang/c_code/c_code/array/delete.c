#include <stdio.h>

#define N 8

int main()
{
	int arr[N] = {6,9,12,8,4,5,3,21};
	int cnt = N;
	int i = 0;

	printf("Before delete:\n");
	for(i = 0;i < cnt;i++)
	{
		printf("%d ",arr[i]);
	}
	putchar('\n');

	for(i = 3 + 1;i < N;i++)
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
