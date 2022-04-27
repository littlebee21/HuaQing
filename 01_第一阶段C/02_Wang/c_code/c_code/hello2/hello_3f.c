#include <stdio.h>

void print_hello();
void print_world();

int main()
{
	print_hello();
	print_world();
	return 0;
}


void print_hello() //函数头
{
	printf("Hello");
}

void print_world() //函数头
{
	printf(" World\n");
}
