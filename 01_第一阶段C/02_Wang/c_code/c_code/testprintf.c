#include <stdio.h>

int main()
{
	int i = 123;
	long l = 456;
	unsigned int u = 19;

	float f = 2.34f;
	double d = 9.76;
	char c = 'K';

	printf("i=%d,l=%ld,u=%u(u=%o,u=%x),f=%f,d=%f,c=%c,str=%s \n",i,l,u,u,u,f,d,c,"qwert");

	printf("i=%6d\n",i);
	printf("i=%-6d\n",i);

	printf("d=%10.1f\n",d);
	printf("d=%-10.1f\n",d);

	printf("Address of f is %p\n",&f);
	return 0;
}
