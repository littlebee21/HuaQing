#include <stdio.h>

#define N 5
int main()
{
	float arr[N] = {0.0f};

	/*指针访问法*/
	float *pf = NULL;
	printf("Please input %d number:\n",N);
	for(pf = arr;pf < arr + N;pf++)
	{
		scanf("%f",pf);
	}

	for(pf = arr;pf < arr + N;pf++)
	{
		printf("%.1f ",*pf);
	}
	printf("\n");
	

	/*地址访问法*/
	/*
	int i = 0;
	printf("Please input %d number:\n",N);

	for(i = 0;i < N;i++)
	{
		scanf("%f",arr+i);
	}
	for(i = 0;i < N;i++)
	{
		printf("%.1f ",*(arr+i));
	}
	printf("\n");
	*/
	return 0;
}
