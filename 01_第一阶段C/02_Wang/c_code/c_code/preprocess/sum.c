#include <stdio.h>

//#define USE_CIRCULATE

int main(int argc,char *argv[])
{
	int sum = 0;
	int n = 0;

	printf("Please input a number:\n");
	scanf("%d",&n);

	if(n <= 0)
	{
		printf("Your input is error\n");
		return 1;
	}

#if !defined USE_CIRCULATE
	printf("Not Use Circulate\n");
	sum = n * (1 + n) / 2;
#else

	{
		int i = 0;

		printf("Use Circulate\n");
		for(i = 1;i <= n;i++)
		{
			sum += i;
		}
	}
#endif
	printf("Sum is %d\n",sum);
	return 0;
}

