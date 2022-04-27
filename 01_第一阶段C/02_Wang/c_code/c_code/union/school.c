#include <stdio.h>

#define NAME_LEN 20
#define LESSON_LEN 16

union data
{
	char lesson[LESSON_LEN];//for teacher
	float score;//for student
};

struct person
{
	char name[NAME_LEN];
	char sex;
	int no;
	int type;//1 teacher  2 student
	union data dt;
};

char *mygets(char *pout,int size);
int output_person(struct person *pt);
int input_person(struct person *pt);
int main(int argc,char *argv[])
{
	struct person t = {""};

	input_person(&t);
	output_person(&t);
	return 0;
}

int output_person(struct person *pt)
{
	switch(pt->type)
	{
		case 1://teacher info
			printf("This is a teacher:\n");
			printf("Name:%s\n",pt->name);
			printf("Sept->%c\n",pt->sex);
			printf("Work-No:%d\n",pt->no);
			printf("Lesson:%s\n",pt->dt.lesson);
			break;
		case 2://student info
			printf("This is a student:\n");
			printf("Name:%s\n",pt->name);
			printf("Sept->%c\n",pt->sex);
			printf("Study-No:%d\n",pt->no);
			printf("Score:%.1f\n",pt->dt.score);
			break;
		default:
			printf("The person type is invalid\n");
			break;
	}

	return 0;
}

int input_person(struct person *pt)
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
	}
	return 0;
}
