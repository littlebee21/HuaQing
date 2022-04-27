#include <stdio.h>

int is_include_3(int n);
int input_number();

int main()
{
	/*输入一个数*/
	int num = input_number();
	int flag = 0;


	/*判断其是否某位是3*/
	flag = is_include_3(num);

	/*输出结果*/
	if(flag)
	{
		printf("%d include 3\n",num);
	}
	else
	{
		printf("%d do not include 3\n",num);
	}
	return 0;
}

int input_number()
{
	int x = 0;

	printf("Please input a number:\n");
	scanf("%d",&x);

	return x;
}

int is_include_3(int n)
{
	while(n != 0 && n % 10 != 3)
	{
		n = n / 10;
	}
	if(0 == n)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
