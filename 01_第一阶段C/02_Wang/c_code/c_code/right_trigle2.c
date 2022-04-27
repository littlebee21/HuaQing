#include <stdio.h>

int main()
{
	int line = 0;//行号
	int st = 0;//星号的个数
	int sp = 0;//空格的个数

	for(line = 1;line <= 6;line++)
	{
		/*打印（6-line）个空格 */
		for(sp = 1;sp <= 6-line;sp++)
		{
			putchar(' ');
		}

		/*打印line个星号*/
		for(st = 1;st <= line;st++)
		{
			putchar('*');
		}

		/*打印一个换行符*/
		putchar('\n');
	}
	return 0;
}
