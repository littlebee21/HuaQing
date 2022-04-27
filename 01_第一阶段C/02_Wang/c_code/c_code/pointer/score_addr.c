#include <stdio.h>

#define N 10
int main()
{
	int arr[N] = {0};
	int i = 0;
	int cnt = N;
	int max = 0;
	int min = 0;
	int sum = 0;

	/*输入10个分数*/
	printf("Please input %d score:\n",cnt);
	for(i = 0;i < cnt;i++)
	{
		scanf("%d",arr+i);
	}


	/*找最大的下标*/
	for(i = 1;i < cnt;i++)
	{
		if(*(arr+i) > *(arr+max))
		{
			max = i;
		}
	}

	/*删除最大元素*/
	for(i = max + 1;i < cnt;i++)
	{
		*(arr+i-1)= *(arr+i);
	}
	cnt--;
	
	/*找最小元素的下标*/
	for(i = 1;i < cnt;i++)
	{
		if(*(arr+i) < *(arr+min))
		{
			min = i;
		}
	}

	/*删除最小元素*/
	for(i = min + 1;i < cnt;i++)
	{
		*(arr+i-1) = *(arr+i);
	}
	cnt--;

	/*求和*/
	for(i = 0;i < cnt;i++)
	{
		sum += *(arr+i);
	}

	/*输出最终得分*/
	printf("Last Score:%.2f\n",(float)sum / cnt);
	return 0;
}
