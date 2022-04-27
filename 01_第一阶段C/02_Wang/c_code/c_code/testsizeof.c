#include <stdio.h>

int main()
{
	int x = 21;
	int y = 0;

	y=sizeof(x++);

	printf("x=%d,y=%d\n",x,y);
	return 0;
}
