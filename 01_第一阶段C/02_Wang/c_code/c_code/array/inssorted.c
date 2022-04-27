#include <stdio.h>

#define N 8
int main()
{
	float arr[N+1] = {1.2,2.3,3.4,4.5,5.6,6.7,7.8,8.9};
	int cnt = N;
	float num = 0.0f;
	int i = 0;

	printf("Please input a float number:\n");
	scanf("%f",&num);

	for(i = cnt - 1;i >= 0;i--)
	{
		if(arr[i] > num)
		{
			arr[i+1] = arr[i];
		}
		else
		{
			break;
		}
	}
	arr[i+1] = num;
	cnt++;

	printf("After insert:\n");
	for(i = 0;i < cnt;i++)
	{
		printf("%.1f ",arr[i]);
	}
	putchar('\n');

	return 0;
}
