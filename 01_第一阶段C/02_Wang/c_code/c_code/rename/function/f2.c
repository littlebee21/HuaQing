#include <stdio.h>

static int f2();
int f1()
{
	printf("Call f1,in %s\n",__FILE__);
	f2();
	return 0;
}

static int f2()
{
	printf("Call f2,in %s\n",__FILE__);
	return 0;
}
