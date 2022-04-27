#include <unistd.h>
#include <stdio.h>

int main(int argc,char *argv[])
{
	printf("hello world");

	write(1,"Hi",2);

	while(1)
	{
	}

	return 0;
}
