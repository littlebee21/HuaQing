#include "person_sl.h"


//建表：给引擎对象和存放批量元素的数组分配空间
struct seqlist *create_seqlist(int maxsize)
{
	struct seqlist *pseq = NULL;

	if(maxsize <= 0)
	{
		printf("Input param is invalid,in %s at %d\n",__FILE__,__LINE__);
		return NULL;
	}

	pseq = (struct seqlist *)malloc(sizeof(struct seqlist));
	if(NULL == pseq)
	{
		printf("Malloc Failed,in %s at %d\n",__FILE__,__LINE__);
		return NULL;
	}
	memset(pseq,0, sizeof(struct seqlist));

	pseq->pt = (T *)malloc(maxsize * sizeof(T));
	if(NULL == pseq->pt)
	{
		printf("Malloc Failed,in %s at %d\n",__FILE__,__LINE__);
		free(pseq);
		pseq = NULL;
		return NULL;
	}
	memset(pseq->pt,0,maxsize * sizeof(T));

	pseq->max = maxsize;

	return pseq;
}

//清空表：
int clear_seqlist(struct seqlist *pseq)
{
    pseq->len = 0;
    memset(pseq->pt,0,pseq->max * sizeof(T));
    return 0;
}

//删表：释放引擎对象和存放批量元素的数组空间
int destroy_seqlist(struct seqlist *pseq)
{
	if(pseq != NULL)
	{
		if(pseq->pt != NULL)
		{
			free(pseq->pt);
			pseq->pt = NULL;
		}
		free(pseq);
		pseq = NULL;
	}

	return 0;
}

//求表长
int get_seqlist_len(struct seqlist *pseq)
{
	return pseq->len;
}

//判空
int is_empty_seqlist(struct seqlist *pseq)
{
    return pseq->len == 0 ? 1 : 0;
}

//判满
int is_full_seqlist(struct seqlist *pseq)
{
    return pseq->len == pseq->max ? 1 : 0;
}

//插入
//头插：新元素插入在下标最小的位置
int insert_at_head(struct seqlist *pseq,T *pnew)
{
	return insert_at_location(pseq,pnew,0);
}

//尾插：新元素插入在len的位置
int insert_at_tail(struct seqlist *pseq,T *pnew)
{
	return insert_at_location(pseq,pnew,pseq->len);
}

//在指定下标位置插入:
int insert_at_location(struct seqlist *pseq,T *pnew,int loc)
{
	int i = 0;

	if(loc < 0 || loc > pseq->len)
	{
		printf("Input param is invalid,in %s at %d\n",__FILE__,__LINE__);
		return -1;
	}

	if(is_full_seqlist(pseq))
	{
		printf("The sequence list is full already,in %s at %d\n",__FILE__,__LINE__);
		return -1;
	}

	for(i = pseq->len - 1;i >= loc;i--)
	{
		memcpy(pseq->pt + i + 1,pseq->pt + i,sizeof(T));
	}
	memcpy(pseq->pt + loc,pnew,sizeof(T));

	pseq->len++;

	return 0;
}

//删除
//头删：删除下标最小的元素
int delete_at_head(struct seqlist *pseq)
{
	return delete_at_location(pseq,0);
}

//尾删：删除下标为len-1的元素
int delete_at_tail(struct seqlist *pseq)
{
	return delete_at_location(pseq,pseq->len-1);
}

//删除指定下标位置的元素：
int delete_at_location(struct seqlist *pseq,int loc)
{
	int i = 0;

	if(loc < 0 || loc >= pseq->len)
	{
		printf("Input param is invalid,in %s at %d\n",__FILE__,__LINE__);
		return -1;
	}

	if(is_empty_seqlist(pseq))
	{
		printf("The sequence list is empty already,in %s at %d\n",__FILE__,__LINE__);
		return -1;
	}

	for(i = loc + 1;i < pseq->len;i++)
	{
		memcpy(pseq->pt + i - 1,pseq->pt + i,sizeof(T));
	}
	pseq->len--;

	return 0;
}

//修改:
int modify(struct seqlist *pseq,int loc,T *pdata)
{
	if(loc < 0 || loc >= pseq->len)
	{
		printf("Input param is invalid,in %s at %d\n",__FILE__,__LINE__);
		return -1;
	}

	memcpy(pseq->pt+loc,pdata,sizeof(T));

	return 0;
}

//查找：
int search_by_name(struct seqlist *pseq,char *name)
{
	T * ptmp = NULL;

	for(ptmp = pseq->pt;ptmp < pseq->pt + pseq->len;ptmp++)
	{
		if(strcmp(name,ptmp->name) == 0)
		{
			break;
		}
	}

	if(ptmp == pseq->pt + pseq->len)
	{
		return -1;
	}
	else
	{
		return ptmp - pseq->pt;
	}
}

static int cmpphone(const void *pv1,const void *pv2)
{
	return strcmp(((T *)pv1)->phone,((T *)pv2)->phone);
}

//排序
int sort_by_phone(struct seqlist *pseq)
{
	qsort(pseq->pt,pseq->len,sizeof(T),cmpphone);
	return 0;
}

//打印所有联系人
int print_all_person(struct seqlist *pseq)
{
	int i = 0;
	
	printf("%-20s%-4s%-20s%-s\n","Name","Sex","Phone","Address");
	for(i = 0;i < pseq->len;i++)
	{
		printf("%-20s%-4c%-20s%-s\n",
		       (pseq->pt+i)->name,
		       (pseq->pt+i)->sex,
		       (pseq->pt+i)->phone,
		       (pseq->pt+i)->address
		      );
	}

	return 0;
}

//打印一个联系人
int print_a_person(T *pele)
{
	printf("Name:%s,Sex:%c,Phone:%s,Address:%s\n",pele->name,pele->sex,pele->phone,pele->address);
	return 0;
}
