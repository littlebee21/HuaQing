#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
int main()
{
	int arr[N] = {0};
	int i = 0;
	int sum = 0;
	float ave = 0.0f;

	srand(time(NULL));

	for(i = 0;i < N;i++)
	{
		arr[i] = rand() % 53 + 23;
	}

	for(i = 0;i < N;i++)
	{
		printf("%d ",arr[i]);
	}
	putchar('\n');

	for(i = 0;i < N;i++)
	{
		sum = sum + arr[i];
	}

	ave = (float)sum / N;

	printf("The sum is %d,The ave is %.2f\n",sum,ave);
	return 0;
}
