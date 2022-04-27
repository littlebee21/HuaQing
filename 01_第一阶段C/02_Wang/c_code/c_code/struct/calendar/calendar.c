#include "calendar.h"

int print_calendar(struct date *pdate)
{
	int days = get_month_days(pdate);
	int week = get_week(pdate);
	int sp = 0;
	int d = 0;

	printf("SUN MON TUE WED THU FRI SAT\n");
	/*打印空格---week * 4*/
	for(sp = 1;sp <= week * 4;sp++)
	{
		putchar(' ');
	}

	for(d = 1;d <= days;d++)
	{
		printf("%-4d",d);
		if((d+week) % 7 == 0)
		{
			putchar('\n');
		}
	}
	putchar('\n');

	return 0;
}
