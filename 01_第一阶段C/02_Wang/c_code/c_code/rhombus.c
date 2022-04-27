#include <stdio.h>

int main()
{
	int line = 0;
	int sp = 0;
	int st = 0;

	/*打印前4行*/
	for(line = 1;line <= 4;line++)
	{
		/*打印4-line个空格*/
		for(sp=1;sp <= 4-line;sp++)
		{
			putchar(' ');
		}

		/*打印2*line-1个星号*/
		for(st=1;st <= 2 * line - 1;st++)
		{
			putchar('*');
		}

		/*打印一个换行*/
		putchar('\n');
	}


	/*打印后3行*/
	for(line = 1;line <= 3;line++)
	{
		/*打印line个空格*/
		for(sp=1;sp <= line;sp++)
		{
			putchar(' ');
		}

		/*打印2*(4-line)-1个星号*/
		for(st=1;st <= 2 * (4-line) - 1;st++)
		{
			putchar('*');
		}

		/*打印一个换行*/
		putchar('\n');
	}
	return 0;
}
