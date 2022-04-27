#ifndef CALENDAR_H
#define CALENDAR_H
/*1. 只能存放非执行语句*/
/*2. 存放多个.c共同用到的一些非执行语句*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct date
{
	int y;
	int m;
	int d;
};

int is_leap_year(struct date *pdate);
int get_month_days(struct date *pdate);
int is_valid_date(struct date *pdate);
int get_year_days(struct date *pdate);
int get_week(struct date *pdate);
int print_calendar(struct date *pdate);





#endif
