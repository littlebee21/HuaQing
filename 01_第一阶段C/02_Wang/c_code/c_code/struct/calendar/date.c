#include "calendar.h"

int is_leap_year(struct date *pdate)
{
	if((pdate->y % 4 == 0 && pdate->y % 100 != 0) || (pdate->y % 400 == 0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int get_month_days(struct date *pdate)
{
	int ret = 0;
	switch(pdate->m)
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
			if(is_leap_year(pdate))
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

int is_valid_date(struct date *pdate)
{
	int days = 0;
	if(pdate->m < 1 || pdate->m > 12)
	{
		return 0;
	}

	days = get_month_days(pdate);
	if(pdate->d < 1 || pdate->d > days)
	{
		return 0;
	}

	return 1;
}

int get_year_days(struct date *pdate)
{
	int i = 0;
	int ret = 0;
	struct date t = {0};

	t.y = pdate->y;
	t.d = 1;

	for(i = 1;i <= pdate->m-1;i++)
	{
		t.m = i;
		ret += get_month_days(&t);
	}

	return ret + pdate->d;
}

int get_week(struct date *pdate)
{
	int sum = 0;

	sum = (pdate->y-1) + 
	      (pdate->y-1)/4 - 
	      (pdate->y-1) / 100 + 
	      (pdate->y-1)/400 + 
	      get_year_days(pdate);

	return sum % 7;
}
