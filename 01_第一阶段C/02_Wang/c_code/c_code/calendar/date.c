
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

int get_month_days(int y,int m)
{
	int ret = 0;
	switch(m)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			ret = 31;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			ret = 30;
			break;
		case 2:
			if(is_leap_year(y))
			{
				ret = 29;
			}
			else
			{
				ret = 28;
			}
			break;
	}

	return ret;
}

int is_valid_date(int y,int m,int d)
{
	int days = 0;
	if(m < 1 || m > 12)
	{
		return 0;
	}

	days = get_month_days(y,m);
	if(d < 1 || d > days)
	{
		return 0;
	}

	return 1;
}

int get_year_days(int y,int m,int d)
{
	int i = 0;
	int ret = 0;

	for(i = 1;i <= m-1;i++)
	{
		ret += get_month_days(y,i);
	}

	return ret + d;
}

int get_year_days(int y,int m,int d);
int get_week(int y,int m,int d)
{
	int sum = 0;

	sum = (y-1) + (y-1)/4 - (y-1) / 100 + (y-1)/400 + get_year_days(y,m,d);

	return sum % 7;
}
