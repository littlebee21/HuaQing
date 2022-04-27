#include <stdio.h>

#define PI 3.14

float input_sr();
float input_lr();
float get_ellipse_area(float l1,float l2);
float get_ellipse_rl(float l1,float l2);
int main()
{
	float r1 = input_lr();
	float r2 = input_sr();

	if(lr <= 0 || sr <= 0)
	{
		printf("Your input is invalid\n");
		return 1;
	}

	printf("The area of ellipse is %.2f\n",get_ellipse_area(r1,r2));
	printf("The round-len of ellipse is %.2f\n",get_ellipse_rl(r1,r2));
	return 0;
}

float get_ellipse_area(float l1,float l2)
{
	return PI * l1 * l2;
}

float get_ellipse_rl(float l1,float l2)
{
	float t = 0.0f;

	if(l1 < l2)
	{
		t = l1;
		l1 = l2;
		l2 = t;
	}

	return 2 * PI * l2 + 4 * (l1 - l2);
}
float input_lr()
{
	float lr = 0.0f;
	
	printf("Please input long-r of ellipse:\n");
	scanf("%f",&lr);

	return lr;
}

float input_sr()
{
	float sr = 0.0f;
	
	printf("Please input short-r of ellipse:\n");
	scanf("%f",&sr);

	return sr;
}
