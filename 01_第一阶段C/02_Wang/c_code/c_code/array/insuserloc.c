#include <stdio.h>

#define N 8
int main()
{
	int arr[N+1] = {6,9,12,8,4,5,3,21};
	int cnt = N;
	int num = 0;
	int i = 0;
	int loc = 0;

	printf("Please input a number:\n");
	scanf("%d",&num);

	printf("Before insert:\n");
	for(i = 0;i < cnt;i++)
	{
		printf("%d ",arr[i]);
	}
	putchar('\n');

	printf("Please input a location[0,%d]:\n",N);
	scanf("%d",&loc);

	if(loc < 0 || loc > N)
	{
		printf("Your input location is invalid\n");
		return 1;
	}

	for(i = cnt-1;i >= loc;i--)
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
