#include <stdio.h>
#include <stdlib.h>

#include <time.h>

int input_number();
int input_sum();
int judge(int u,int us,int p,int ps);
int do_you_continue();
int main()
{
	int pnum = 0;
	int psum = 0;
	int unum = 0;
	int usum = 0;
	int ret = 0;
	
	srand(time(NULL));

	do
	{
		/*程序产生一个【0，5】随机数----手指*/
		pnum = rand() % 6;

		/*程序产生一个【1，5】随机数--- 和*/
		psum = rand() % 6  + pnum;

		/*用户输入一个【0，5】数字 ---- 手指*/
		unum = input_number();

		/*用户输入一个【0，10】数字 ---- 和*/
		usum = input_sum();

		/*判断输赢*/
		ret = judge(unum,usum,pnum,psum);
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

int judge(int u,int us,int p,int ps)
{
	int uok = 0;
	int pok = 0;

	if(u+p == us)
	{
		uok = 1;
	}
	if(u+p == ps)
	{
		pok = 1;
	}

	if(uok == pok)
	{
		return 0;
	}
	else
	{
		if(uok)
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
		printf("Please input your number[0,5]:\n");
		scanf("%d",&x);

		while(getchar() != '\n')
		{
		}

		if(x < 0 || x >5)
		{
			printf("Your num is invalid,please re-input\n");
			redo = 1;
		}
	}while(redo);

	return x;
}

int input_sum()
{
	int x = -1;
	int redo = 0;

	do
	{
		redo = 0;
		printf("Please input your sum[0,10]:\n");
		scanf("%d",&x);

		while(getchar() != '\n')
		{
		}

		if(x < 0 || x >10)
		{
			printf("Your sum is invalid,please re-input\n");
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
