#include <stdio.h>

int input_number();

int search_number(int *parr,int cnt,int n);
int insert_number(int *parr,int cnt,int n);
int delete_number(int *parr,int cnt,int l);
int print_array(int *parr,int cnt);

#define N 8
int main()
{
	int arr[N+1] = {2,4,6,8,10,12,14,16};
	int cnt = N;
	int num = 0;
	int loc = -1;

	/*用户输入一个数---->num*/
	num = input_number();

	/*在数组查找num ----->loc*/
	loc = search_number(arr,cnt,num);

	if(loc < 0)
	{//没找到，做插入
		insert_number(arr,N+1,num);
		cnt++;
	}
	else
	{//找到，做删除
		delete_number(arr,cnt,loc);
		cnt--;
	}

	/*输出操作后的数组*/
	print_array(arr,cnt);

	return 0;
}

int input_number()
{
	int x = 0;

	printf("Please input your number:\n");
	scanf("%d",&x);

	while(getchar() != '\n')
	{
	}

	return x;
}
