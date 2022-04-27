#include <stdio.h>

int main()
{
	char ch = '\0';

	printf("Please input a char:\n");
	scanf("%c",&ch);

	if(ch >= 'A' && ch <= 'Z')
	{
		ch = ch + ('a' - 'A');
		printf("ch=%c\n",ch);
	}
	else
	{
		printf("%c is not upper-char\n",ch);
	}
	return 0;
}
