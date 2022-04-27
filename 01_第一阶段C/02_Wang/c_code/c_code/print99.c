#include <stdio.h>

int main()
{
	int l = 0;//行号
	int c = 0;//列号

	/*打印第一行（列号）*/
	printf("  %-7d%-7d%-7d%-7d%-7d%-7d%-7d%-7d%-7d\n",1,2,3,4,5,6,7,8,9);

	/*打印后9行*/
	for(l = 1;l<=9;l++)	
	{
		/*打印行号*/
		printf("%-2d",l);

		/*打印l个乘积式子*/
		for(c=1;c<=l;c++)
		{
			printf("%d*%d=%-2d ",l,c,l*c);
		}

		/*打印一个换行*/
		putchar('\n');
	}

	return 0;
}
