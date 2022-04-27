#include <stdio.h>
#include <math.h>

int input_number();
int is_prime(int n);

int main()
{
	int num = input_number();

	if(num <= 1)
	{
		printf("Your input is invalid\n");
		return 1;
	}

	if(is_prime(num))
	{
		printf("%d is prime\n",num);
	}
	else
	{
		printf("%d is not prime\n",num);
	}
	return 0;
}

int is_prime(int n)
{
	int i = 0;
	int r = sqrt(n);

	//for(i = 2;i <= n-1;i++)
	for(i = 2;i <= r;i++)
	{
		if(n % i == 0)
		{
			break;
		}
	}

	if(i == r+1)
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
