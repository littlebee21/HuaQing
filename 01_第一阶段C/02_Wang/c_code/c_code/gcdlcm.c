#include <stdio.h>

int get_lcm(int x,int y);
int get_gcd(int x,int y);
int input_number();

int main()
{
	int n1 = input_number();
	int n2 = input_number();

	if(n1 < 1 || n2 < 1)
	{
		printf("Your input number is not natrue-number\n");
		return 1;
	}

	printf("GCD of %d and %d is %d\n",get_gcd(n1,n2),n1,n2);
	printf("LCM of %d and %d is %d\n",get_lcm(n1,n2),n1,n2);
	return 0;
}

int input_number()
{
	int num = 0;

	printf("Please input a number:\n");
	scanf("%d",&num);

	while(getchar() != '\n')
	{
	}

	return num;
}

int get_gcd(int x,int y)
{
	int t = 0;

	t = x % y;
	while(t != 0)
	{
		x = y;
		y = t;
		t = x % y;
	}

	return y;
}

int get_lcm(int x,int y)
{
	int t = 0;

	if(x < y)
	{
		t = x;
		x = y;
		y = t;
	}

	for(t = 1;t <= y;t++)
	{
		if((t * x) % y == 0)
		{
			break;
		}
	}

	return t*x;
}

