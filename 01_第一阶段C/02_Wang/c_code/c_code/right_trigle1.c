#include <stdio.h>

int main()
{
	int i = 0;//行号
	int j = 0;//星号的个数

	for(i = 1;i <= 6;i++)
	{
		/*打印i个星号*/
		for(j = 1;j <= i;j++)
		{
			putchar('*');
		}

		/*打印一个换行符*/
		putchar('\n');
	}
	return 0;
}
