#ifndef STU_H
#define STU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 20
struct stu
{
	int no;
	char name[NAME_LEN];
	char sex;
	float math;
	float english;
	float chinese;
};

struct myclass
{
	int cnt;
	int max;
	int lastno;
	struct stu *pt;
};

//#define PRINT_ERROR
#ifdef PRINT_ERROR
#define MyPrint printf("Error:in %s at %d-",__FILE__,__LINE__);printf
#else
#define MyPrint(...)  
#endif

/*stumodel.c*/
struct myclass * create_stuinfo_mem(int maxsize);
int destroy_stuinfo_mem(struct myclass *pcls);

int insert_student_at_tail(struct myclass *pcls,struct stu *pst);
int delete_student(struct myclass *pcls,int loc);
int modify_student(struct myclass *pcls,int loc,struct stu *pnew);
int search_student_by_no(struct myclass *pcls,int no);
int search_student_by_name(struct myclass *pcls,char *name);

int sort_total_by_insert(struct stu *pst,int cnt);
int sort_math_by_select(struct stu *pst,int cnt);
int sort_english_by_bubble(struct stu *pst,int cnt);
int sort_chinese_by_insert(struct stu *pst,int cnt);

/*mygets.c*/
char *mygets(char *pout,int size);


/*ui.c*/
int input_operation();
int print_all_student(struct myclass *pcls);
int input_a_new_stuinfo(struct stu *pst);
int print_user_info(char *pstr);

#endif
