#include <stdio.h>

int input_number();

int main()
{
	int n1 = input_number();
	int n2 = input_number();
	int y = 0;
	int r = 0;

	while(n1 >= n2)
	{
		r++;
		n1 = n1 - n2;
	}
	y = n1;
	
	printf("r = %d,y = %d\n",r,y);

	return 0;
}

int input_number()
{
	int x = 0;

	printf("Please input a number:\n");
	scanf("%d",&x);

	while(getchar() != '\n')
	{
	}

	return x;
}
