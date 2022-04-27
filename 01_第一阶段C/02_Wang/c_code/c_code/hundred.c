#include <stdio.h>

int main()
{
	int m = 0;
	int f = 0;
	int l = 0;

	for(m = 0;m <=20;m++)
	{
		/*当公鸡数是m时罗列所有的母鸡数和小鸡数*/
		for(f=0;f <= 33;f++)
		{
			/*当公鸡数数为m，母鸡数为f时，罗列所有小鸡数*/
			/*for(l = 0;l <= 300;l++)
			{
				if(m+f+l == 100 && 5 * m + 3 * f + l / 3 == 100 && l % 3 == 0)
				{
					printf("m=%d,f=%d,l=%d\n",m,f,l);
				}
			}*/

			/*求出小鸡数*/
			l = 100 - m -f;
			if(l % 3 == 0 && 5 * m + 3 * f + l / 3 == 100)
			{
				printf("m=%d,f=%d,l=%d\n",m,f,l);
			}
		}
	}

	return 0;
}
