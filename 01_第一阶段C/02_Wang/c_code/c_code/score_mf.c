#include <stdio.h>

char get_level(int fen);
int input_score();
int main()
{
	int score = input_score();

	char ret = get_level(score);

	printf("Your score-level is %c\n",ret);
	return 0;
}

char get_level(int fen)
{
	char lv = '\0';

	if(fen >= 90)
	{
		lv = 'A';
	}
	else if(fen >= 80)
	{
		lv = 'B';
	}
	else if(fen >= 70)
	{
		lv = 'C';
	}
	else if(fen >= 60)
	{
		lv = 'D';
	}
	else
	{
		lv = 'E';
	}

	return lv;
}

int input_score()
{
	int sc = 0;
	
	printf("Please input your score:\n");
	scanf("%d",&sc);

	return sc;
}
