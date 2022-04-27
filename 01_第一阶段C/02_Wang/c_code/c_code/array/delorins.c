#include <stdio.h>

#define N 8
int main()
{
	int arr[N+1] = {2,4,6,8,10,12,14,16};
	int cnt = N;
	int num = 0;
	int loc = -1;
	int i = 0;

	/*用户输入一个数---->num*/
	printf("Please input your number:\n");
	scanf("%d",&num);

	/*在数组查找num ----->loc*/
	for(i = 0;i < cnt;i++)
	{
		if(num == arr[i])
		{
			loc = i;
			break;
		}
	}

	if(loc < 0)
	{//没找到，做插入
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
	}
	else
	{//找到，做删除
		for(i = loc + 1;i < cnt;i++)
		{
			arr[i-1] = arr[i];
		}
		cnt--;
	}

	/*输出操作后的数组*/
	for(i = 0;i < cnt;i++)
	{
		printf("%d ",arr[i]);
	}
	putchar('\n');

	return 0;
}
