#include <stdio.h>

int main()
{
	int line = 0;
	int sp = 0;
	int ch = 0;

	for(line = 1;line <= 26;line++)
	{
		for(sp = 1;sp <= 26 - line;sp++)
		{
			putchar(' ');
		}

		for(ch = 1;ch <= 2 * line - 1;ch++)
		{
			putchar('A' + line - 1);
		}

		putchar('\n');
	}

	return 0;
}
