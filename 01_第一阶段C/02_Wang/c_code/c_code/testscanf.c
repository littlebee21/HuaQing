#include <stdio.h>

int main()
{
	int x = 0;
	char c = '\0';

	printf("Please input a number:\n");

	scanf("%4d",&x);

	printf("x=%d\n",x);	

	printf("Please input a char:\n");

	scanf("%c",&c);
	scanf("%c",&c);

	printf("c=%c\n",c);
	return 0;
}
