#include <stdio.h>

#define N 8
int main()
{
	int arr[N] = {85,32,66,73,52,46,27,12};
	int i = 0;//轮数
	int j = 0;//协助每轮在【0，N-1-i】间将最大元素通过多次的比较交换到下标N-i位置
	int t = 0;//协助完成下标j的元素与下标j+1的元素交换

	for(i = 0;i < N;i++)
	{
		/*在【0，N-1-i】间将最大元素通过多次的比较交换到下标N-i位置*/
		for(j = 0;j < N - 1 - i;j++)
		{
			if(arr[j] > arr[j+1])
			{
				t = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = t;
			}
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
