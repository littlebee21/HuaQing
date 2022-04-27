#include <stdio.h>
#include <math.h>

int main()
{
	int num = 0;
	int g = 0;
	int s = 0;
	int h = 0;

	for(num = 100;num <= 999;num++)
	{
		g = num % 10;
		s = (num / 10)%10;
		h = num / 100;

		if(pow(g,3) + pow(s,3) + pow(h,3) == num)
		{
			printf("%d ",num);
		}
	}

	putchar('\n');
	return 0;
}
