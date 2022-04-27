#include <stdio.h>

#define PI 3.14
int main()
{
	float lr = 0.0f;
	float sr = 0.0f;
	float area = 0.0f;
	float rl = 0.0f;

	printf("Please input long-r of ellipse:\n");
	scanf("%f",&lr);

	printf("Please input short-r of ellipse:\n");
	scanf("%f",&sr);

	if(lr <= 0 || sr <= 0)
	{
		printf("Your input is invalid\n");
		return 1;
	}

	area = PI * lr *sr;

	if(lr < sr)
	{
		float t = 0.0f;

		t = lr;
		lr = sr;
		sr = t;
	}

	rl =2 * PI * sr + 4 * (lr - sr);

	printf("The area of ellipse is %.2f\n",area);
	printf("The round-len of ellipse is %.2f\n",rl);
	return 0;
}
