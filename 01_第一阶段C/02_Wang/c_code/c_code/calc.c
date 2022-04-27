#include <stdio.h>

int main()
{
	int num1 = 0;
	int num2 = 0;
	char op = '\0';
	int ret = 0;
	int flag = 1;

	printf("Please input the first number:\n");
	scanf("%d",&num1);
	scanf("%c",&op);

	printf("Please input the operator-char:\n");
	scanf("%c",&op);

	printf("Please input the second number:\n");
	scanf("%d",&num2);

	switch(op)
	{
		case '+':
			ret = num1 + num2;
			break;
		case '-':
			ret = num1 - num2;
			break;
		case '*':
			ret = num1 * num2;
			break;
		case '/':
			if(num2 != 0)
			{
				ret = num1 / num2;
			}
			else
			{
				flag = 0;
				printf("num2 is zero,can not operate\n");
			}
			break;
		default:
			flag = 0;
			printf("The operate is not supported\n");
			break;
	}

	if(flag)
	{
		printf("%d %c %d = %d\n",num1,op,num2,ret);
	}

	return 0;
}
