#include "person_ll.h"

//建表：给引擎对象分配空间
struct linklist *create_linklist()
{
	struct linklist *pll = NULL;

	pll = (struct linklist *)malloc(sizeof(struct linklist));
	if(NULL == pll)
	{
		printf("Malloc failed,in %s at %d\n",__FILE__,__LINE__);
		return NULL;
	}
	memset(pll,0,sizeof(struct linklist));

	return pll;
}

//清空表：将所有节点空间释放，置头节点的len成员为0，pfirst成员为NULL
int clear_linklist(struct linklist *plink)
{
	struct node *pnode = NULL;
	struct node *pnext = NULL;

	pnode = plink->pfirst;
	while(pnode != NULL)
	{
		pnext = pnode->pnext;
		destroy_node(pnode);
		pnode = pnext;
	}

	plink->pfirst = NULL;
	plink->len = 0;

	return 0;
}

//删表：先清空表，然后再释放头节点的空间
int destroy_linklist(struct linklist *plink)
{
	if(plink != NULL)
	{
		clear_linklist(plink);
		free(plink);
		plink = NULL;
	}
	return 0;
}

//创建一个节点
struct node *create_node(T *pdata)
{
	struct node *pnew = NULL;

	pnew = (struct node *)malloc(sizeof(struct node));
	if(NULL == pnew)
	{
		printf("Malloc failed,in %s at %d\n",__FILE__,__LINE__);
		return NULL;
	}
	memset(pnew,0,sizeof(struct node));

	memcpy(&pnew->data,pdata,sizeof(T));

	return pnew;
}

//销毁一个节点：释放节点占用的内存空间
int destroy_node(struct node *pnode)
{
	if(pnode != NULL)
	{
		free(pnode);
		pnode = NULL;
	}

	return 0;
}

//求表长
int get_linklist_len(struct linklist *plink)
{
	return plink->len;
}

//判空
int is_empty_linklist(struct linklist *plink)
{
	return plink->len <= 0 ? 1 : 0;
}


//插入
//头插：新节点插入链表，作为链表中的第一节点
int insert_at_head(struct linklist *plink,struct node *pnew)
{
	if(NULL == plink || NULL == pnew)
	{
		printf("Input param is invalid,in %s at %d\n",__FILE__,__LINE__);
		return -1;
	}
	pnew->pnext = plink->pfirst;
	plink->pfirst = pnew;

	plink->len++;

	return 0;
}

/*获取带头节点的单向非循环链表的最后一个节点的地址*/
static struct node *get_last_node(struct linklist *plink)
{
	struct node *plast = NULL;

	plast = plink->pfirst;
	while(plast != NULL)
	{
		if(plast->pnext == NULL)
		{
			break;
		}
		plast = plast->pnext;
	}

	return plast;
}

//尾插：新元素插入链表，作为链表中的最后一个节点
int insert_at_tail(struct linklist *plink,struct node *pnew)
{
	struct node *plast = NULL;
	
	if(NULL == plink || NULL == pnew)
	{
		printf("Input param is invalid,in %s at %d\n",__FILE__,__LINE__);
		return -1;
	}

	/*得到最后一个节点地址赋值给plast指针变量*/
	plast = get_last_node(plink);

	if(plast != NULL)
	{//原表为非空表
		plast->pnext = pnew;
	}
	else
	{//原表为空表
		plink->pfirst = pnew;
	}
	pnew->pnext = NULL;

	plink->len++;

	return 0;
}

static int is_in_linklist(struct linklist *plink,struct node *pnode)
{
	struct node *pt = NULL;

	pt = plink->pfirst;
	while(pt != NULL)
	{
		if(pt == pnode)
		{
			break;
		}

		pt = pt->pnext;
	}

	return NULL == pt ? 0 : 1;
}

//在指定节点后插入新节点:
int insert_at_after_node(struct linklist *plink,struct node *pnode,struct node *pnew)
{
		
	if(NULL == plink || NULL == pnew || NULL == pnode)
	{
		printf("Input param is invalid,in %s at %d\n",__FILE__,__LINE__);
		return -1;
	}

	/*如果不确定pnode指向节点是链表中的节点时，需要检查其在链表*/
	if(!is_in_linklist(plink,pnode))
	{
		printf("The pnode is not in the linklist,in %s at %d\n",__FILE__,__LINE__);
		return -1;
	}

	pnew->pnext = pnode->pnext;
	pnode->pnext = pnew;

	plink->len++;

	return 0;
}

//移除
//头移除：将第一个节点脱链
struct node * remove_at_head(struct linklist *plink)
{
	struct node *ptemp = NULL;

	if(NULL == plink)
	{
		printf("Input param is invalid,in %s at %d\n",__FILE__,__LINE__);
		return NULL;
	}
	if(is_empty_linklist(plink))
	{
		printf("The linklist is empty already,remove_at_head failed,in %s at %d\n",__FILE__,__LINE__);
		return NULL;
	}

	ptemp = plink->pfirst;
	plink->pfirst = ptemp->pnext;
	ptemp->pnext = NULL;

	plink->len--;

	return ptemp;
}

static struct node *get_beforelast_node(struct linklist *plink)
{
	struct node *pbefore = NULL;
	struct node *plast = NULL;

	plast = plink->pfirst;
	while(plast != NULL)
	{
		if(plast->pnext == NULL)
		{
			break;
		}
		pbefore = plast;
		plast = plast->pnext;
	}

	return pbefore;
}

//尾移除：将最后一个节点脱链
struct node * remove_at_tail(struct linklist *plink)
{
	struct node *pbeforelast = NULL;
	struct node *plast = NULL;

	if(NULL == plink)
	{
		printf("Input param is invalid,in %s at %d\n",__FILE__,__LINE__);
		return NULL;
	}
	if(is_empty_linklist(plink))
	{
		printf("The linklist is empty already,remove_at_tail failed,in %s at %d\n",__FILE__,__LINE__);
		return NULL;
	}

	pbeforelast = get_beforelast_node(plink);
	if(NULL == pbeforelast)
	{//原表仅有一个节点时
		plast = plink->pfirst;
		plink->pfirst = NULL;
	}
	else
	{//原表中节点数 >= 2
		plast = pbeforelast->pnext;
		pbeforelast->pnext = NULL;
	}

	plink->len--;

	return plast;
}

static struct node *get_before_node(struct linklist *plink,struct node *pnode)
{
	struct node *pbefore = NULL;
	struct node *ptemp = NULL;

	ptemp = plink->pfirst;
	while(ptemp != NULL)
	{
		if(ptemp == pnode)
		{
			break;
		}
		pbefore = ptemp;
		ptemp = ptemp->pnext;
	}

	if(ptemp == NULL)
	{
		return NULL;
	}
	else
	{
		return pbefore;
	}
}

//移除指定节点
#ifndef USING_SWAP
int remove_a_node(struct linklist *plink,struct node *pnode)
{
	struct node *pbefore = NULL;

	if(NULL == plink || NULL == pnode)
	{
		printf("Input param is invalid,in %s at %d\n",__FILE__,__LINE__);
		return -1;
	}
	if(is_empty_linklist(plink))
	{
		printf("The linklist is empty already,remove_a_node failed,in %s at %d\n",__FILE__,__LINE__);
		return -1;
	}

	/*获取指定节点前一个节点的地址*/
	pbefore = get_before_node(plink,pnode);
	if(NULL == pbefore)
	{
		if(pnode == plink->pfirst)
		{//指定节点为链表中的第一个节点
			remove_at_head(plink);
			return 0;
		}
		else
		{//指定节点不是链表中的节点，不能完成移除
			printf("The node is not in linklist,remove_a_node failed,in %s at %d\n",__FILE__,__LINE__);
			return -1;
		}
	}
	else
	{//原表中不止一个节点，并且指定节点不是第一节点
		pbefore->pnext = pnode->pnext;
		pnode->pnext = NULL;

		plink->len--;
	}
	return 0;
}
#else
struct node * remove_a_node(struct linklist *plink,struct node *pnode)
{
	struct node *ptemp = NULL;

	if(NULL == plink || NULL == pnode)
	{
		printf("Input param is invalid,in %s at %d\n",__FILE__,__LINE__);
		return NULL;
	}
	if(is_empty_linklist(plink))
	{
		printf("The linklist is empty already,remove_a_node failed,in %s at %d\n",__FILE__,__LINE__);
		return NULL;
	}
	if(!is_in_linklist(plink,pnode))
	{
		printf("The node is not in linklist,remove_a_node failed,in %s at %d\n",__FILE__,__LINE__);
		return NULL;
	}

	if(pnode->pnext != NULL)
	{
		T t;

		ptemp = pnode->pnext;	
		memcpy(&t,&pnode->data,sizeof(T));
		memcpy(&pnode->data,&ptemp->data,sizeof(T));
		memcpy(&ptemp->data,&t,sizeof(T));

		pnode->pnext = ptemp->pnext;
		ptemp->pnext = NULL;

		plink->len--;
	}
	else
	{
		ptemp = remove_at_tail(plink);
	}
	return ptemp;
}
#endif

//修改:
int modify(struct node *pnode,T *pdata)
{
	memcpy(&pnode->data,pdata,sizeof(T));

	return 0;
}

//查找：
struct node * search_by_name(struct linklist *plink,char *name)
{
	struct node *pt = NULL;

	pt = plink->pfirst;
	while(pt != NULL)
	{
		if(strcmp(name,pt->data.name) == 0)
		{
			break;
		}

		pt = pt->pnext;
	}

	return pt;
}

static int insert_between_nodes(struct linklist *plink,struct node *pbefore,struct node* pnode,struct node *pnew)
{
	if(NULL == plink || NULL == pnode)
	{
		printf("Input param is invalid,%s:%d\n",__FILE__,__LINE__);
		return -1;
	}

	if(pbefore != NULL)
	{
		if(pbefore->pnext != pnode)
		{
			printf("pbefore node is not before pnode,%s:%d\n",__FILE__,__LINE__);
			return -1;
		}
		pnew->pnext = pnode;
		pbefore->pnext = pnew;
		plink->len++;
	}
	else
	{//头插
		pnew->pnext = pnode;
		plink->pfirst = pnew;
		plink->len++;
	}
	return 0;
}

static int insert_after_lastnode(struct linklist *plink,struct node* plast,struct node *pnew)
{
	plast->pnext = pnew;
	pnew->pnext = NULL;
	plink->len++;

	return 0;
}
//排序
int sort_by_phone(struct linklist *plink)
{
	struct linklist templink = {0,NULL};
	struct node *pnew = NULL;
	struct node *pbefore = NULL;
	struct node *ptemp = NULL;

	if(plink->pfirst == NULL || plink->pfirst->pnext == NULL)
	{
		return 0;
	}

	templink.pfirst = plink->pfirst->pnext;
	templink.len = plink->len - 1;

	plink->pfirst->pnext = NULL;
	plink->len = 1;

	pnew = remove_at_head(&templink);
	while(pnew != NULL)
	{
		pbefore = NULL;
		ptemp = plink->pfirst;
		while(ptemp != NULL)
		{
			if(strcmp(ptemp->data.phone,pnew->data.phone) > 0)
			{//before insert
				insert_between_nodes(plink,pbefore,ptemp,pnew);
				break;
			}
			else
			{
				pbefore = ptemp;
				ptemp = ptemp->pnext;
			}
		}
		if(ptemp == NULL)
		{//last insert
			insert_after_lastnode(plink,pbefore,pnew);
		}
		
		pnew = remove_at_head(&templink);
	}


	return 0;
}

static int phonecmp(const void *pv1,const void *pv2)
{
	return strcmp((*(struct node **)pv1)->data.phone,(*(struct node **)pv2)->data.phone);
}

struct node **sort_person_linklist_by_phone(struct linklist *plink)
{
	struct node **ppsorted = NULL;
	struct node *ptemp = NULL;
	int i = 0;

	ppsorted = (struct node **)malloc(plink->len * sizeof(struct node *));
	if(NULL == ppsorted)
	{
		printf("Malloc Failed,%s:%d\n",__FILE__,__LINE__);
		return NULL;
	}
	memset(ppsorted,0,plink->len * sizeof(struct node *));

	ptemp = plink->pfirst;
	while(ptemp != NULL)
	{
		*(ppsorted + i) = ptemp;
		i++;
		ptemp = ptemp->pnext;
	}

	qsort(ppsorted,plink->len,sizeof(struct node *),phonecmp);

	return ppsorted;
}

int print_sort_result(struct node **ppsorted,int cnt)
{
	int i = 0;

	printf("%-20s%-4s%-20s%-s\n","Name","Sex","Phone","Address");

	for(i = 0;i < cnt;i++)
	{
		printf("%-20s%-4c%-20s%-s\n",
		       (*(ppsorted+i))->data.name,
		       (*(ppsorted+i))->data.sex,
		       (*(ppsorted+i))->data.phone,
		       (*(ppsorted+i))->data.address
		      );
	}

	return 0;
}

int free_sort_result(struct node **ppsorted)
{
	if(ppsorted != NULL)
	{
		free(ppsorted);
		ppsorted = NULL;
	}

	return 0;
}

//打印所有联系人
int print_all_person(struct linklist *plink)
{
	struct node *pnode = NULL;

	printf("%-20s%-4s%-20s%-s\n","Name","Sex","Phone","Address");

	pnode = plink->pfirst;
	while(pnode != NULL)
	{
		printf("%-20s%-4c%-20s%-s\n",
		       pnode->data.name,
		       pnode->data.sex,
		       pnode->data.phone,
		       pnode->data.address
		      );
		pnode = pnode->pnext;
	}
	return 0;
}

//打印一个联系人
int print_a_person(struct node *pnode)
{
	printf("Name:%s,Sex:%c,Phone:%s,Address:%s\n",
		pnode->data.name,
		pnode->data.sex,
		pnode->data.phone,
		pnode->data.address
	      );
	return 0;
}

