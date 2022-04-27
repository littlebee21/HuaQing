#include "calendar.h"

int input_year_and_month(struct date *pdate);
int main()
{
	struct date dt = {0,0,1};

	input_year_and_month(&dt);

	if(!is_valid_date(&dt))
	{
		printf("Your input error\n");
		return 1;
	}

	print_calendar(&dt);
	return 0;
}

int input_year_and_month(struct date *pdate)
{

	printf("Please input year:\n");
	scanf("%d",&pdate->y);
	while(getchar() != '\n')
	{
	}

	printf("Please input month:\n");
	scanf("%d",&pdate->m);
	while(getchar() != '\n')
	{
	}
	return 0;
}

