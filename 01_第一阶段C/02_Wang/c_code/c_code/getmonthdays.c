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
	int sum = 0;

	/*判断月份的合法性*/
	if(m < 1 || m > 12)
	{
		return -1;
	}

	/*计算合法月份的总天数*/
	switch(m)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			sum = 31;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			sum = 30;
			break;
		case 2:
			if(is_leap_year(y))
			{
				sum = 29;
			}
			else
			{
				sum = 28;
			}
			break;
	}
	return sum;
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
