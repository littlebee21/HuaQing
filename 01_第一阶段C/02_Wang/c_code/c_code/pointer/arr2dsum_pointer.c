#include <stdio.h>

#define N 4
#define M 4
int main()
{
	int arr[N][M] = {{0}};
	int i = 0;
	int *p = 0;
	int sum = 0;

	printf("Please input %d * %d numbers:\n",N,M);
	for(i = 0;i < N;i++)
	{
		for(p = *(arr+i);p < *(arr+i) + M;p++)
		{
			scanf("%d",p);
		}
	}

	for(i = 0;i < N;i++)
	{
		for(p = *(arr+i);p < *(arr+i) + M;p++)
		{
			if(0 == i || 0 == p-(*(arr+i)) || N-1 == i || M-1 == p-(*(arr+i)))
			{
				sum += *p;
			}
		}
	}

	printf("The sum is %d\n",sum);

	return 0;
}
