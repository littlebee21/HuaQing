#include <stdio.h>

float get_ellipse_rl(float lr,float sr);
#define PI 3.14

int main()
{
	float l1 = 0.0f;
	float l2 = 0.0f;
	float rl = 0.0f;

	printf("Please input two length:\n");
	scanf("%f%f",&l1,&l2);

	rl = get_ellipse_rl(l1,l2);
	printf("The first call get_ellipse_rl,rl=%f\n",rl);
	
	l1 = 1.4+2;
	l2 = 3.6+2;

	rl = get_ellipse_rl(l1,l2);
	printf("The second call get_ellipse_rl,rl=%f\n",rl);

	return 0;
}

float get_ellipse_rl(float lr,float sr)
{
	float t=0;

	if(lr < sr)
	{
		t = lr;
		lr = sr;
		sr = t;
	}

	return 2 * PI * sr + 4 * (lr - sr);
}
