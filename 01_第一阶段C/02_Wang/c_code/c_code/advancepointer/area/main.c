#include "area.h"

int input_shape();
float input_length();

int main(int argc,char *argv[])
{
	int which = 0;
	float l1 = 0.0f;
	float l2 = 0.0f;
	float area = 0.0f;
	float (*pf)(float,float) = NULL;


	//A处：决定后续会用哪个函数去求面积
	which = input_shape();
	switch(which)
	{
		case 1://rectangle
			//pf = get_area_of_rectangle;
			pf = &get_area_of_rectangle;
			break;
		case 2://ellpise
			//pf = get_area_of_ellipse;
			pf = &get_area_of_ellipse;
			break;
		case 3://triangle
			//pf = get_area_of_triangle;
			pf = &get_area_of_triangle;
			break;
		default:
			break;
	}

	l1 = input_length();
	l2 = input_length();


	//B处：通过间接调用函数指针指向的函数去求面积
	if(pf != NULL)
	{
		//area = pf(l1,l2);
		area = (*pf)(l1,l2);
		printf("The area is %.2f\n",area);
	}
	else
	{
		printf("Can not get area\n");
	}


	return 0;
}

float input_length()
{
	float len = 0.0f;

	printf("Please input a length:\n");
	scanf("%f",&len);

	while(getchar() != '\n')
	{
	}
	return len;
}

int input_shape()
{
	int sh = 0;

	printf("Please input your select:\n");
	printf("1. Get Area of Rectangle\n");
	printf("2. Get Area of ellipse\n");
	printf("3. Get Area of Triangle\n");
	printf("0. Exit\n");
	scanf("%d",&sh);

	while(getchar() != '\n')
	{
	}

	return sh;
}
