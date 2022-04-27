#include <stdio.h>

#define N 6
int main()
{
	int arr[N+1] = {0};
	int i = 0;
	int num = 0;

	/*数组输入*/
	printf("Please input %d number:\n",N);
	for(i = 0;i < N;i++)
	{
		scanf("%d",&arr[i]);
	}

	/*用户输入要查找的数*/
	printf("Please input a number:\n");
	scanf("%d",&num);

	/*在数组中查找num，找到则输出第一出现的下标位置，没找到则打印Not found*/
	arr[N] = num;
	for(i = 0;arr[i] != num;i++)
	{
	}
	if(i == N)
	{
		printf("Not found\n");
	}
	else
	{
		printf("%d at %d\n",num,i);
	}



	return 0;
}
