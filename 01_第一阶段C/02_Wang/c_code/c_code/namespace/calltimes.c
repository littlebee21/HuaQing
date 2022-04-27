#include <stdio.h>

/*
int func();
int main(int argc,char *argv[])
{
	int i = 0;

	for(i = 0;i < 5;i++)
	{
		printf("in main,call func %d\n",func());
	}
	return 0;
}

int func()
{
	static int t = 0;//main函数被调用前，本条语句已经被执行完毕，不会再次被执行

	t++;
	printf("The func is called,%dth\n",t);

	return t;
}
*/


int * func();
int main(int argc,char *argv[])
{
	int *pret = NULL;
	int i = 0;

	for(i = 0;i < 5;i++)
	{
		pret = func();
		printf("in main,call func %d\n",*pret);
	}
	*pret = 100;
	pret = func();
	return 0;
}
int * func()
{
	static int t = 0;

	t++;
	printf("The func is called,%dth\n",t);
	return &t;
}

