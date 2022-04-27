#include <stdio.h>

#define N 5
int main()
{
	float arr[N] = {0.0f};
	int i = 0;


	printf("Please input %d number:\n",N);
	for(i = 0;i < N;i++)
	{
		scanf("%f",&arr[i]);
	}

	for(i = 0;i < N;i++)
	{
		printf("%.1f ",arr[i]);
	}
	printf("\n");
	return 0;
}
