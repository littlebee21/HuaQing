#include <stdio.h>

struct my_complex
{
	double r;
	double v;
};

int main(int argc,char *argv[])
{
	struct my_complex t1 = {0.0};
	struct my_complex t2 = {0.0};
	struct my_complex t3 = {0.0};


	printf("Please input real-value and virtual-value:\n");
	scanf("%lf%lf",&t1.r,&t1.v);
	
	printf("Please input real-value and virtual-value:\n");
	scanf("%lf%lf",&t2.r,&t2.v);

	t3.r = t1.r + t2.r;
	t3.v = t1.v + t2.v;

	printf("After add,r-value=%.2f,v-value=%.2f\n",t3.r,t3.v);
	return 0;
}
