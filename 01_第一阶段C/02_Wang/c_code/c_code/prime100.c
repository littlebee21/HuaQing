#include <stdio.h>

int is_prime(int n);
int main()
{
	int num = 0;

	for(num = 2;num < 100;num++)
	{
		if(is_prime(num))
		{
			printf("%d ",num);
		}

	}

	putchar('\n');

	return 0;
}

int is_prime(int n)
{
	int i = 0;

	for(i = 2;i <= n - 1;i++)
	{
		if(n % i == 0)
		{
			break;
		}
	}

	if(i == n)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
