#include <stdio.h>

int input_number();
int is_perfect_num(int num);


int main()
{
	int n = input_number();

	if(n <= 0)
	{
		printf("Your input error\n");
		return 1;
	}
	
	if(is_perfect_num(n))
	{
		printf("%d is perfect number\n",n);
	}
	else
	{
		printf("%d is not perfect number\n",n);
	}
	return 0;
}

int is_perfect_num(int num)
{
	int sum = 0;
	int i = 0;

	for(i = 1;i <= num - 1;i++)
	{
		if(num % i == 0)
		{
			sum = sum + i;
		}
	}
	if(sum == num)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int input_number()
{
	int x = 0;

	printf("Please input a number:\n");
	scanf("%d",&x);

	while(getchar() != '\n')
	{
	}

	return x;
}
