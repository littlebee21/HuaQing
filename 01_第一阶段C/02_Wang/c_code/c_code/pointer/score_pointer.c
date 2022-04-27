#include <stdio.h>

#define N 10
int main()
{
	int arr[N] = {0};
	int cnt = N;
	int max = 0;
	int min = 0;
	int sum = 0;
	int *pi = NULL;

	/*输入10个分数*/
	printf("Please input %d score:\n",cnt);
	for(pi = arr;pi <arr + cnt;pi++)
	{
		scanf("%d",pi);
	}


	/*找最大的下标*/
	for(pi = arr+1;pi < arr + cnt;pi++)
	{
		if(*pi > *(arr+max))
		{
			max = pi - arr;
		}
	}

	/*删除最大元素*/
	for(pi = arr + max + 1;pi < arr+cnt;pi++)
	{
		*(pi-1) = *pi;
	}
	cnt--;
	
	/*找最小元素的下标*/
	for(pi = arr + 1;pi <arr + cnt;pi++)
	{
		if(*pi < *(arr+min))
		{
			min = pi - arr;
		}
	}

	/*删除最小元素*/
	for(pi = arr + min + 1;pi < arr + cnt;pi++)
	{
		*(pi-1) = *pi;
	}
	cnt--;

	/*求和*/
	for(pi = arr;pi < arr + cnt;pi++)
	{
		sum += *pi;
	}

	/*输出最终得分*/
	printf("Last Score:%.2f\n",(float)sum / cnt);
	return 0;
}
