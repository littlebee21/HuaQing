#include <stdio.h>

int fib(int n);
int main(int argc,char *argv[])
{
	int x = 0;

	if(argc < 2)
	{
		printf("The argument is too few\n");
		return 1;
	}

	sscanf(argv[1],"%d",&x);

	printf("The n month have %d rabits\n",fib(x));

	return 0;
}

int fib(int n)
{
	if(n == 1 || n == 2)
	{
		return 1;
	}

	return fib(n-1) + fib(n-2);
}
