#include <stdio.h>

int is_hui1(char arr[],int cnt);
int is_hui2(char arr[],int start,int end);
int is_hui3(char start[],char end[]);
int is_hui4(char start[]);//只能用在有特殊元素作为结束标记的数组
int main()
{
	char arr1[5] = {'a','b','c','b','a'};
	char arr2[6] = {'a','b','c','c','b','a'};
	char arr3[5] = {'a','b','c','d','a'};
	char arr4[6] = {'a','b','c','e','b','a'};
	char arr5[6] = {'a','b','b','a','\0','a'};

	if(is_hui1(&arr1[0],5))//if(is_hui(arr1,5))
	{
		printf("arr1 is huiwen\n");
	}	

	if(is_hui2(&arr2[0],0,5))
	{
		printf("arr2 is huiwen\n");
	}	
	if(is_hui3(&arr3[0],&arr3[4]))
	{
		printf("arr3 is huiwen\n");
	}	
	if(is_hui3(&arr4[0],&arr4[5]))
	{
		printf("arr4 is huiwen\n");
	}	
	if(is_hui4(arr5))
	{
		printf("arr5 is huiwen\n");
	}	
	return 0;
}

int is_hui1(char arr[],int cnt)
{
	int flag = 1;
	int i = 0;
	int j = 0;

	for(i=0,j=cnt-1;i < cnt / 2;i++,j--)
	{
		if(arr[i] != arr[j])
		{
			flag = 0;
			break;
		}
	}

	return flag;
}

int is_hui2(char arr[],int start,int end)
{
	int flag = 1;
	int i = 0;
	int j = 0;

	for(i = start,j=end;i < (end-start+1)/2;i++,j--)
	{
		if(arr[i] != arr[j])
		{
			flag = 0;
			break;
		}
	}

	return flag;
}

int is_hui3(char start[],char end[])
{
	int flag = 1;
	int cnt = end - start + 1;
	int i = 0;
	int j = 0;

	for(i = 0,j =cnt-1;i < cnt/2;i++,j--)
	{
		if(start[i] != start[j])
		{
			flag = 0;
			break;
		}
	}

	return flag;
}

int is_hui4(char start[])
{
	int i = 0;
	int end = 0;
	int j = 0;
	int flag = 1;

	while(start[i]!='\0')
	{
		i++;
	}
	end = i;

	for(i = 0,j =end-1;i < end/2;i++,j--)
	{
		if(start[i] != start[j])
		{
			flag = 0;
			break;
		}
	}

	return flag;
}
