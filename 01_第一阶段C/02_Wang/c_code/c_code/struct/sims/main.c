#include "stu.h"

int mainloop(struct myclass *pcls);
int main(int argc,char *argv[])
{
	int max = 0;
	struct myclass *pcls = NULL;

	if(argc < 2)
	{
		printf("The argument is too few,Usage:./sims maxsize\n");
		return 1;
	}
	sscanf(argv[1],"%d",&max);

	if(max <= 0)
	{
		printf("The max argument is invalid\n");
		return 2;
	}

	pcls = create_stuinfo_mem(max);

	if(pcls != NULL)
	{		
		mainloop(pcls);
	}
	else
	{
		return 3; 
	}

	destroy_stuinfo_mem(pcls);
	pcls = NULL;
	return 0;
}

int mainloop(struct myclass *pcls)
{
	int exitflag = 0;
	int cmd = 0;
	struct stu t = {0};
	int ret = 0;

	while(1)
	{
		cmd = input_operation();
		switch(cmd)
		{
			case 1://add
				input_a_new_stuinfo(&t);
				ret = insert_student_at_tail(pcls,&t);	
				if(ret)
				{
					print_user_info("Insert a new student failed\n");
				}
				break;
			case 2://delete
				break;
			case 3://search
				break;
			case 4://modify
				break;
			case 5://sort by total-score
				sort_total_by_insert(pcls->pt,pcls->cnt);
				print_all_student(pcls);
				break;
			case 6://sort by math-score
				sort_math_by_select(pcls->pt,pcls->cnt);
				print_all_student(pcls);
				break;
			case 7://sort by english-score
				sort_english_by_bubble(pcls->pt,pcls->cnt);
				print_all_student(pcls);
				break;
			case 8://sort by chinese-score
				sort_chinese_by_insert(pcls->pt,pcls->cnt);
				print_all_student(pcls);
				break;
			case 0:
				exitflag = 1;
				break;
		}//end of switch
		if(exitflag)
		{
			break;
		}
	}//end of while(1)

	return 0;
}
