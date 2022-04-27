#include <stdio.h>

void print_hello();
void print_world();
void print_helloworld();

int main()
{
	print_helloworld();
	return 0;
}

void print_helloworld()
{
	print_hello();
	print_world();
}

void print_hello() //函数头
{
	printf("Hello");
}

void print_world() //函数头
{
	printf(" World\n");
}
