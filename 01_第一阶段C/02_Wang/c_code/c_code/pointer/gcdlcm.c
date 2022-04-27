#include <stdio.h>

int get_lcm(int x,int y);
int get_gcd(int x,int y);

int main(int argc,char *argv[])
{
	int n1 = 0;
	int n2 = 0;

	if(argc < 3)
	{
		printf("The argument is too few,Usage:./gcdlcm num1 num2\n");
		return 1;
	}

	sscanf(argv[1],"%d",&n1);
	sscanf(argv[2],"%d",&n2);


	if(n1 < 1 || n2 < 1)
	{
		printf("Your input number is not natrue-number\n");
		return 2;
	}

	printf("GCD of %d and %d is %d\n",get_gcd(n1,n2),n1,n2);
	printf("LCM of %d and %d is %d\n",get_lcm(n1,n2),n1,n2);
	return 0;
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

