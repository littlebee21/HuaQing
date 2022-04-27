#include <stdio.h>
#include <stdlib.h>

#include <time.h>

int main()
{
	int pnum = 0;//pc number
	int unum = 0;//user number

	srand(time(NULL));

	pnum = rand() % 10 + 1;

	do
	{
		/*用户输入一个数*/
		printf("Please input a number:\n");
		scanf("%d",&unum);

		/*判断unum < pnum，是则输出太小*/
		if(unum < pnum)
		{
			printf("Your input too small\n");
		}
		
		/*判断unum > pnum，是则输出太大*/
		if(unum > pnum)
		{
			printf("Your input too big\n");
		}

	}while(unum != pnum);

	printf("You are right!\n");

	return 0;
}
