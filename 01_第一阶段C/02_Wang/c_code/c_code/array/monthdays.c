#include <stdio.h>

int input_month();
int input_year();
int is_leap_year(int y);
int get_month_days(int y,int m);
int main()
{
	/*输入年月*/
	int year = input_year();
	int month = input_month();
	int days = 0;

	/*计算该月总天数*/
	days = get_month_days(year,month);

	/*输出该月总天数*/
	if(days > 0)
	{
		printf("Ther are %d days in %d-%d\n",days,year,month);
	}
	else
	{
		printf("Your input month is invalid\n");
	}
	return 0;
}

int get_month_days(int y,int m)
{
	int leap_year_days[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
	int common_year_days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

	/*判断月份的合法性*/
	if(m < 1 || m > 12)
	{
		return -1;
	}

	/*计算合法月份的总天数*/
	if(is_leap_year(y))
	{
		return leap_year_days[m-1];
	}
	else
	{
		return common_year_days[m-1];
	}
}

int is_leap_year(int y)
{
	if((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int input_year()
{
	int y = 0;

	printf("Please input a year:\n");
	scanf("%d",&y);

	return y;
}

int input_month()
{
	int m = 0;

	printf("Please input a month:\n");
	scanf("%d",&m);

	return m;
}
