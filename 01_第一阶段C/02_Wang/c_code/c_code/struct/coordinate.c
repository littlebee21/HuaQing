#include <stdio.h>

struct pointer
{
	float x;
	float y;
};

int main(int argc,char *argv[])
{
	struct pointer pt = {0.0f};

	printf("Please input x and y:\n");
	scanf("%f%f",&pt.x,&pt.y);

	if(pt.x == 0 && pt.y == 0)
	{
		printf("It is (0,0)\n");
	}
	else if(pt.x == 0 && pt.y != 0)
	{
		printf("It is at y-axle\n");
	}
	else if(pt.x != 0 && pt.y == 0)
	{
		printf("It is at x-axle\n");
	}
	else
	{
		if(pt.x > 0 && pt.y > 0)
		{
			printf("It is at the first quadrant\n");
		}
		else if(pt.x < 0 && pt.y > 0)
		{
			printf("It is at the second quadrant\n");
		}
		else if(pt.x < 0 && pt.y < 0)
		{
			printf("It is at the third quadrant\n");
		}
		else
		{
			printf("It is at the fourth quadrant\n");
		}

	}

	return 0;
}
