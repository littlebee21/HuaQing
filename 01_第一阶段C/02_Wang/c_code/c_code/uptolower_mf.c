#include <stdio.h>

char input_char();
char up_to_lower(char x);
int main()
{
	char c = input_char();

	printf("After change, c is %c\n",up_to_lower(c));
	return 0;
}

char up_to_lower(char x)
{
	if(x >= 'A' && x <= 'Z')
	{
		return x + ('a' - 'A');
	}
	else
	{
		return x;
	}
}

char input_char()
{
	char ch = '\0';

	printf("Please input a char:\n");
	scanf("%c",&ch);

	return ch;
}
