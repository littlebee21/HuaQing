#include <stdio.h>

const int gx = 100;//位于数据区的，因为有const修饰，因此其空间被做到了只读数据分区中，只读数据分区程序不能任何手段进行修改，一旦修改程序就崩溃
int main(int argc,char *argv[])
{
	const int x = 10;//x的空间位于栈区
	//int *p = &x;//警告：&x得到的地址值类型是const int *,而p空间中存放的int *
	int *p = (int *)&x;

	//x = 20; //编译错误，不能通过变量名直接修改
	
	*p = 20;

	printf("x=%d\n",x);


	//gx = 200; //编译错误，不能通过变量名直接修改
	p = (int *)&gx;

	//*p = 200;//程序崩溃，原因是试图修改只读数据区

	printf("gx=%d\n",gx);
	return 0;
}
