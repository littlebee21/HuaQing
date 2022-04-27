#include <stdio.h>

int get_month_days(int y,int m);
int get_week(int y,int m,int d);
int print_calendar(int y,int m)
{
	int days = get_month_days(y,m);
	int week = get_week(y,m,1);
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
