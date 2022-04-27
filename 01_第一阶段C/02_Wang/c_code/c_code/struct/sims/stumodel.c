#include "stu.h"

struct myclass * create_stuinfo_mem(int maxsize)
{
	struct myclass *pcls = NULL;

	pcls = (struct myclass *)malloc(sizeof(struct myclass));
	if(NULL == pcls)
	{
		MyPrint("Malloc failed for myclass\n");
		return NULL;
	}
	memset(pcls,0,sizeof(struct myclass));

	pcls->max = maxsize;
	pcls->lastno = 1;
	pcls->pt = (struct stu *)malloc(maxsize * sizeof(struct stu));
	if(NULL == pcls->pt)
	{
		MyPrint("Malloc failed for student\n");
		free(pcls);
		pcls = NULL;
		return NULL;
	}
	memset(pcls->pt,0,maxsize * sizeof(struct stu));

	return pcls;
}

int destroy_stuinfo_mem(struct myclass *pcls)
{
	free(pcls->pt);
	pcls->pt = NULL;

	free(pcls);
	pcls = NULL;

	return 0;
}

int is_full(struct myclass *pcls)
{
	return pcls->cnt >= pcls->max ? 1 : 0;
}

int is_empty(struct myclass *pcls)
{
	return pcls->cnt <= 0 ? 1 : 0;
}

int insert_student_at_tail(struct myclass *pcls,struct stu *pst)
{
	if(is_full(pcls))
	{
		MyPrint("The stuinfo mem is already full\n");
		return -1;
	}

	memcpy(pcls->pt + pcls->cnt,pst,sizeof(struct stu));
	(pcls->pt+pcls->cnt)->no = pcls->lastno;
	pcls->lastno++;
	pcls->cnt++;

	return 0;
}

int delete_student(struct myclass *pcls,int loc)
{
	struct stu *ptemp = NULL;

	if(is_empty(pcls))
	{
		MyPrint("The stuinfo mem is already empty\n");
		return -1;
	}
	if(loc < 0 || loc >= pcls->cnt)
	{
		MyPrint("input param loc is invalid\n");
		return -1;
	}

	for(ptemp = pcls->pt + loc + 1;ptemp < pcls->pt + pcls->cnt;ptemp++)
	{
		memcpy(ptemp - 1,ptemp,sizeof(struct stu));
	}

	pcls->cnt--;
	
	return 0;
}

int modify_student(struct myclass *pcls,int loc,struct stu *pnew)
{
	if(loc < 0 || loc >= pcls->cnt)
	{
		MyPrint("input param loc is invalid\n");
		return -1;
	}

	memcpy(pcls->pt + loc,pnew,sizeof(struct stu));

	return 0;
}

int search_student_by_no(struct myclass *pcls,int no)
{
	int i = 0;

	for(i = 0;i < pcls->cnt;i++)
	{
		if((pcls->pt + i)->no == no)
		{
			break;
		}
	}

	if(i == pcls->cnt)
	{
		return -1;
	}
	else
	{
		return i;
	}
}

int search_student_by_name(struct myclass *pcls,char *name)
{
	struct stu *ptemp = NULL;

	for(ptemp = pcls->pt;ptemp < pcls->pt + pcls->cnt;ptemp++)
	{
		if(strcmp(ptemp->name,name) == 0)
		{
			break;
		}
	}
	if(ptemp == pcls->pt + pcls->cnt)
	{
		return -1;
	}
	else
	{
		return ptemp - pcls->pt;
	}
}

int sort_total_by_insert(struct stu *pst,int cnt)
{
	int i = 0;
	int j = 0;
	struct stu t = {0};

	for(i = 1;i < cnt;i++)
	{
		memcpy(&t,pst+i,sizeof(struct stu));
		for(j = i-1;j >= 0;j--)
		{
			if( ((pst + j)->math + 
			     (pst + j)->english +
			     (pst + j)->chinese) < 
			    (t.math + t.english + t.chinese)
			  )
			{
				memcpy(pst + j + 1,pst+j,sizeof(struct stu));
			}
			else
			{
				break;
			}
		}
		memcpy(pst + j + 1,&t,sizeof(struct stu));
	}

	return 0;
}

int sort_math_by_select(struct stu *pst,int cnt)
{
	return 0;
}

int sort_english_by_bubble(struct stu *pst,int cnt)
{
	return 0;
}

int sort_chinese_by_insert(struct stu *pst,int cnt)
{
	int i = 0;
	int j = 0;
	struct stu t = {0};

	for(i = 1;i < cnt;i++)
	{
		memcpy(&t,pst+i,sizeof(struct stu));
		for(j = i-1;j >= 0;j--)
		{
			if( (pst + j)->chinese < t.chinese)
			{
				memcpy(pst + j + 1,pst+j,sizeof(struct stu));
			}
			else
			{
				break;
			}
		}
		memcpy(pst + j + 1,&t,sizeof(struct stu));
	}

	return 0;
}
