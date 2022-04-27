#include <stdio.h>

void my_print_string(char *pstr);
int main(int argc,char *argv[])
{
	my_print_string("Hello Wolrd");
	putchar('\n');
	return 0;
}

void my_print_string(char *pstr)
{
	if(*pstr == '\0')
	{
		return;
	}
	my_print_string(pstr+1);
	putchar(*pstr);
}
