#include <stdio.h>

int main()
{
	int a = 0;
	int b = 0;
	int num = 0; 
	int i = 0;

	for(a = 1;a <= 9;a++)
	{
		for(b = 0;b <= 9;b++)
		{
			num = a * 1000 + a * 100 + b * 10 + b;
			for(i = 31;i < 100;i++)
			{
				if( i * i == num)
				{
					break;
				}
			}
			if(i < 100)
			{
				printf("%d * %d = %d\n",i,i,num);
			}
		}
	}
	return 0;
}
