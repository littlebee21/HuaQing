#include <stdio.h>

int input_month();
int input_year();

int is_valid_date(int y,int m,int d);
int print_calendar(int y,int m);
int main()
{
	int year = input_year();
	int month = input_month();

	if(!is_valid_date(year,month,1))
	{
		printf("Your input error\n");
		return 1;
	}

	print_calendar(year,month);
	return 0;
}

int input_year()
{
	int y = 0;

	printf("Please input year:\n");
	scanf("%d",&y);

	while(getchar() != '\n')
	{
	}
	return y;
}

int input_month()
{
	int m = 0;

	printf("Please input month:\n");
	scanf("%d",&m);

	while(getchar() != '\n')
	{
	}
	return m;
}
