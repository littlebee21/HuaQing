#include <stdio.h>

static int f2();
int f11()
{
	printf("Call f1,in %s\n",__FILE__);
	f2();
	return 0;
}

static int f11()
{
	printf("Call f2,in %s\n",__FILE__);
	return 0;
}

//f11不能重名
