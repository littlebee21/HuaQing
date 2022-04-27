#include <stdio.h>

int main()
{
	int f = 0;//50 --- 2
	int tw = 0;//20 --- 5
	int te;//10 --- 10
	
	for(f = 0;f <= 2;f++)
	{
		for(tw = 0;tw <= 5;tw++)
		{
			for(te = 0;te <= 10;te++)
			{
				if(f * 50 + tw * 20 + te * 10 == 100)
				{
					printf("%d * 50 + %d * 20 + %d * 10 = 100\n",f,tw,te);
				}
			}
		}
	}
	return 0;
}
