#include "school.h"


int output_math_teacherinfo(struct person *pt,int cnt)
{
	struct person *p = NULL;
	int num = 0;

	for(p = pt;p < pt + cnt;p++)
	{
		if(p->type == TEA)
		{
			if(strcmp(p->dt.lesson,"math") == 0)
			{
				num++;
				printf("This is a teacher:\n");
				printf("Name:%s\n",p->name);
				printf("Sept->%c\n",p->sex);
				printf("Work-No:%d\n",p->no);
				printf("Lesson:%s\n",p->dt.lesson);
			}
		}
	}
	if(num == 0)
	{
		printf("No math teacher info\n");
	}

	return 0;
}

float get_student_avescore(struct person *pt,int cnt)
{
	float total = 0;
	struct person *p = NULL;
	int num = 0;

	for(p = pt;p < pt + cnt;p++)
	{
		if(p->type == STU)
		{
			num++;
			total += p->dt.score;
		}
	}

	if(num != 0)
	{
		return total / num;
	}
	else
	{
		printf("No student data,get avescore failed\n");
		return -1.0;
	}
}

int input_one_person(struct person *pt);
int input_persons(struct person *pt,int cnt)
{
	struct person *p = NULL;

	for(p = pt;p < pt + cnt;p++)
	{
		input_one_person(p);
	}
	return 0;
}

int input_one_person(struct person *pt)
{
	printf("please input a name:\n");
	mygets(pt->name,NAME_LEN);

	printf("please input a sex\n");
	pt->sex= getchar();
	while(getchar() != '\n')
	{
	}

	printf("please input a no:\n");
	scanf("%d",&pt->no);
	while(getchar() != '\n')
	{
	}

	printf("Please select type:\n");
	printf("1. teacher\n");
	printf("2. student\n");
	scanf("%d",&pt->type);
	while(getchar() != '\n')
	{
	}

	if(pt->type == 1)
	{
		printf("Please input a lesson name:\n");
		mygets(pt->dt.lesson,LESSON_LEN);
	}
	else if(pt->type == 2)
	{
		printf("Please input a score:\n");
		scanf("%f",&pt->dt.score);
		while(getchar() != '\n')
		{
		}
	}
	return 0;
}
