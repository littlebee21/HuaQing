#include <stdio.h>

#define N 8
int main()
{
	int arr[N+1] = {6,9,12,8,4,5,3,21};
	int cnt = N;
	int num = 0;
	int i = 0;

	printf("Please input a number:\n");
	scanf("%d",&num);

	printf("Before insert:\n");
	for(i = 0;i < cnt;i++)
	{
		printf("%d ",arr[i]);
	}
	putchar('\n');

	for(i = cnt-1;i >= 4;i--)
	{
		arr[i+1] = arr[i];
	}
	arr[i+1] = num;
	cnt++;

	printf("After insert:\n");
	for(i = 0;i < cnt;i++)
	{
		printf("%d ",arr[i]);
	}
	putchar('\n');
	return 0;
}
