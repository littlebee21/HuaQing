#include <stdio.h>
extern int gx;//gx的声明语句
static int gv;//f2.c中的gv定义语句，非声明
void f3()
{
	printf("in f3,gx=%d\n",gx);
	printf("in f3,gv=%d\n",gv);
}


