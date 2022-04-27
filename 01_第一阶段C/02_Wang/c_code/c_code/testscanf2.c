#include <stdio.h>

char input_char();
int input_number();

int main()
{
	/*输入一个整型数*/
	int n = input_number();

	/*输入一个第一个字符*/
	char c1 = input_char();

	/*输入第二个字符*/
	char c2 = input_char();

	/*打印数和两个字符*/
	printf("n = %d,c1=%c,c2=%c\n",n,c1,c2);
	return 0;
}

int input_number()
{
	int x = 0;

	printf("Please input a number:\n");
	scanf("%d",&x);

	{//清空本轮输入多余的字符	
		while(getchar() != '\n')
		{
		}
	}
	return x;
}

char input_char()
{
	char ch= 0;

	printf("Please input a char:\n");
	scanf("%c",&ch);

	while(getchar() != '\n')
	{
	}

	return ch;
}
