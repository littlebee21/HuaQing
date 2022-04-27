#include <stdio.h>

int factor(int n);
int main(int argc,char *argv[])
{
	printf("4!=%d\n",factor(4));

	return 0;
}

int factor(int n)
{/*
	if(n <= 2)
	{
		return 2;
	}
*/
	return n * factor(n-1);
}
