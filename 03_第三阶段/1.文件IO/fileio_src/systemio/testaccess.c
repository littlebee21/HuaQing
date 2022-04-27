#include <unistd.h>

#include <stdio.h>

int main(int argc,char *argv[])
{
	if(argc < 2)
	{
		printf("The argument is too few,Usage:./isexist file\n");
		return 1;
	}

	if(!access(argv[1],F_OK))
	{
		printf("The %s file is exist\n",argv[1]);
	}
	else
	{
		printf("The %s file is not exist\n",argv[1]);
	}

	return 0;
}
