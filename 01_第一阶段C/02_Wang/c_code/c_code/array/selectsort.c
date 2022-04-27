#include <stdio.h>

#define N 8
int main()
{
	int arr[N] = {85,32,66,73,52,46,27,12};
	int i = 0;//轮数
	int j = 0;//协助每轮在【i，N-1】间找最小元素的下标
	int min = 0;//存放每轮最小元素的下标
	int t = 0;//协助完成下标min的元素与下标i的元素交换

	for(i = 0;i < N;i++)
	{
		/*在[i,N-1]间找最小元素下标，结果存放在min空间中*/
		min = i;
		for(j = i+1;j < N;j++)
		{
			if(arr[j] < arr[min])
			{
				min = j;
			}
		}

		/*下标min的元素与下标i的元素进行交换*/
		if(min != i)
		{
			t = arr[min];
			arr[min] = arr[i];
			arr[i] = t;
		}
	}

	printf("After sort:\n");
	for(i = 0;i < N;i++)
	{
		printf("%d ",arr[i]);
	}
	putchar('\n');

	return 0;
}
