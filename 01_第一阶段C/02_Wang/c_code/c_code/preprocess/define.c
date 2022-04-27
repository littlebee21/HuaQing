#include <stdio.h>

#define NAME(a) #a
#define T(a) a##1

int main()
{
	int T(x);
	printf("%s\n",NAME(hello));
	x1 = 2;
	printf("x1=%d\n",x1);

	printf("some info in %s at %d\n",__FILE__,__LINE__);
	printf("some info in %s at %d\n",__FILE__,__LINE__);
	printf("some info in %s at %d\n",__FILE__,__LINE__);
	return 0;
}
