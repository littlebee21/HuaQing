#include "stu.h"

int input_operation()
{
	int op = 0;

	printf("##########################################\n");
	printf("1. Add a new student\n");
	printf("2. delete a student\n");
	printf("3. search a student\n");
	printf("4. modify a student-info\n");
	printf("5. sort all students by total-score\n");
	printf("6. sort all students by math-score\n");
	printf("7. sort all students by english-score\n");
	printf("8. sort all students by chinese-score\n");
	printf("0. Exit\n");
	printf("##########################################\n");

	scanf("%d",&op);

	while(getchar() != '\n')
	{
	}
	return op;
}

int print_all_student(struct myclass *pcls)
{
	struct stu *ptemp = NULL;

	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	printf("No  Name                    Sex Math    English Chinese Total\n");
	for(ptemp = pcls->pt;ptemp < pcls->pt + pcls->cnt;ptemp++)
	{
		printf("%-4d%-24s%-4c%-8.1f%-8.1f%-8.1f%-8.1f\n",
				ptemp->no,
				ptemp->name,
				ptemp->sex,
				ptemp->math,
				ptemp->english,
				ptemp->chinese,
				ptemp->math + ptemp->english + ptemp->chinese
		      );

	}
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");

	return 0;
}

int input_a_new_stuinfo(struct stu *pst)
{
	printf("Please input new student name:\n");
	mygets(pst->name,NAME_LEN);

	printf("Please input new student sex:\n");
	pst->sex = getchar();
	while(getchar() != '\n')
	{
	}

	printf("Please input new student max-score:\n");
	scanf("%f",&pst->math);
	while(getchar() != '\n')
	{
	}

	printf("Please input new student english-score:\n");
	scanf("%f",&pst->english);
	while(getchar() != '\n')
	{
	}

	printf("Please input new student chinese-score:\n");
	scanf("%f",&pst->chinese);
	while(getchar() != '\n')
	{
	}

	return 0;
}

int print_user_info(char *pstr)
{
	return printf("%s",pstr);
}
