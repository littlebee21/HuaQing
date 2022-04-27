#include <stdio.h>
#include <stdlib.h>

#include <time.h>

int input_number();
int judge(int u,int p);
int do_you_continue();
int main()
{
	int pnum = 0;
	int unum = 0;
	int ret = 0;
	
	srand(time(NULL));

	do
	{
		/*程序产生一个【0，2】随机数*/
		pnum = rand() % 3;

		/*用户输入一个【0，2】数字*/
		unum = input_number();

		/*判断输赢*/
		ret = judge(unum,pnum);
		if(ret == 0)
		{
			/*输出平*/
			printf("Peace\n");
		}
		else
		{
			if(ret > 0)
			{
				/*输出赢*/
				printf("You win\n");
			}
			else
			{
				/*输出输*/
				printf("You lost\n");
			}
		}
	}while(/*用户选择是否继续*/do_you_continue());

	printf("Game Over\n");
	return 0;
}

int judge(int u,int p)
{
	if(u == p)
	{
		return 0;
	}
	else
	{
		if((u+1)%3 == p)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
}

int input_number()
{
	int x = -1;
	int redo = 0;

	do
	{
		redo = 0;
		printf("Please input your select:\n");
		printf("0 stone\n");
		printf("1 scissor\n");
		printf("2 paper\n");
		scanf("%d",&x);

		while(getchar() != '\n')
		{
		}

		if(x < 0 || x >2)
		{
			printf("Your select is invalid,please reselect\n");
			redo = 1;
		}
	}while(redo);

	return x;
}

int do_you_continue()
{
	char ch = '\0';

	printf("Do you continue,Y/y\n");
	ch = getchar();

	while(getchar() != '\n')
	{
	}

	if(ch == 'Y' || ch == 'y')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
