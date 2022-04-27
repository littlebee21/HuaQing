#include <stdio.h>

int main(int argc,char *argv[])
{
	float l = 0.0f;
	float w = 0.0f;

	if(argc < 3)
	{
		printf("The argument is too few\n");
		printf("Usage:./garea len width\n");
		return 1;
	}

	sscanf(argv[1],"%f",&l);
	sscanf(argv[2],"%f",&w);

	printf("The area of rectangle is %.2f\n",l*w);

	return 0;
}
