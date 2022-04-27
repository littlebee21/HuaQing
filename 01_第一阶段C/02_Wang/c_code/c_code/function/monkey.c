#include <stdio.h>

int peach(int d);
int main(int argc,char *argv[])
{
	printf("The number of peach at first day is %d\n",peach(1));

	return 0;
}

int peach(int d)
{
	if(d == 10)
	{
		return 1;
	}

	return (peach(d+1) + 1) * 2;
}
