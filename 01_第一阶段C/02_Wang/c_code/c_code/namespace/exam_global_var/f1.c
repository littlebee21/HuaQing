#include <stdio.h>
int gx = 11;//gx的定义语句

static int gv;//f1.c中gv的声明语句
void f2()
{
	printf("in f2,gx=%d\n",gx);
	printf("in f2,gv=%d\n",gv);
}



static int gv = 110;//f1.c中gv的定义语句

void f1()
{
	printf("Call f1\n");
	gx += 2;
	gv += 2;
}
