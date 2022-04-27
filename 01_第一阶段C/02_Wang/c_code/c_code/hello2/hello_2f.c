#include <stdio.h>

void print_helloworld();//函数声明语句：函数头;  ----- C语言语法要求调用函数前要书写函数声明语句

int main()
{
	print_helloworld();//函数调用语句：函数名(实参列表)
	return 0;
}


/*函数定义：
返回值类型   函数名（形参列表）
{

	函数体

}
 */
void print_helloworld() //函数头
{
	printf("Hello World\n");
}
