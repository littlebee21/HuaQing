#include <stdio.h>

#define N 4
#define M 4
int main()
{
	int arr[N][M] = {{0}};
	int i = 0;
	int j = 0;
	int sum = 0;

	printf("Please input %d * %d numbers:\n",N,M);
	for(i = 0;i < N;i++)
	{
		for(j = 0;j < M;j++)
		{
			scanf("%d",&arr[i][j]);
		}
	}

	for(i = 0;i < N;i++)
	{
		for(j = 0;j < M;j++)
		{
			if(0 == i || 0 == j || N-1 == i || M-1 ==j)
			{
				sum += arr[i][j];
			}
		}
	}

	printf("The sum is %d\n",sum);

	return 0;
}
