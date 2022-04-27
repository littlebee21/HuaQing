#include <stdio.h>

#define N 8
int main()
{
	int arr[N+1] = {2,4,6,8,10,12,14,16};
	int cnt = N;
	int num = 0;
	int loc = -1;
	int *pi = NULL;

	/*用户输入一个数---->num*/
	printf("Please input your number:\n");
	scanf("%d",&num);

	/*在数组查找num ----->loc*/
	for(pi = arr;pi < arr + cnt;pi++)
	{
		if(num == *pi)
		{
			loc = pi - arr;
			break;
		}
	}

	if(loc < 0)
	{//没找到，做插入
		for(pi = arr + cnt - 1;pi >= arr;pi--)
		{
			if(*pi > num)
			{
				*(pi+1) = *pi;
			}
			else
			{
				break;
			}
		}
		*(pi+1) = num;
		cnt++;
	}
	else
	{//找到，做删除
		for(pi = arr + loc + 1;pi < arr + cnt;pi++)
		{
			*(pi-1) = *pi;
		}
		cnt--;
	}

	/*输出操作后的数组*/
	for(pi = arr;pi < arr+cnt;pi++)
	{
		printf("%d ",*pi);
	}
	putchar('\n');

	return 0;
}
