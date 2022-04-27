#include <stdio.h>

int main()
{
	int score = 0;
	char lv = '\0';

	printf("Please input your score:\n");
	scanf("%d",&score);

	if(score >= 90)
	{
		lv = 'A';
	}
	else if(score >= 80)
	{
		lv = 'B';
	}
	else if(score >= 70)
	{
		lv = 'C';
	}
	else if(score >= 60)
	{
		lv = 'D';
	}
	else
	{
		lv = 'E';
	}

	printf("Your score-level is %c\n",lv);
	return 0;
}
