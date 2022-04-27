#include <stdio.h>

int input_op_char();
int input_number();
int calc(int n1,char which,int n2);
int main()
{
	/*
	 *输入num1 运算符符号 num2 
	 */
	int num1 = input_number();
	char op = input_op_char();
	int num2 = input_number();
	int ret = 0;


	/*根据输入op符号进行四则运算*/
	if(op == '+' || op == '-' || op == '*' || (op == '/' && num2 != 0))
	{
		ret = calc(num1,op,num2);
	}
	else
	{
		printf("Can not operate!\n");
		return 1;
	}


	/*输出运算结果*/
	printf("%d %c %d = %d\n",num1,op,num2,ret);
	return 0;
}

int calc(int n1,char which,int n2)
{
	int x = 0;
	switch(which)
	{
		case '+':
			x = n1 + n2;
			break;
		case '-':
			x = n1 - n2;
			break;
		case '*':
			x = n1 * n2;
			break;
		case '/':
			x = n1 / n2;
			break;
	}
	return x;
}

int input_number()
{
	int x = 0;
	char ch = '\0';

	printf("Please input a number:\n");
	scanf("%d",&x);

	scanf("%c",&ch);

	return x;
}

int input_op_char()
{
	char ch = '\0';

	printf("Please input a operate_char:\n");
	scanf("%c",&ch);

	return ch;
}
