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
		if(pnode == plink->pfirst)
		{
			break;
		}
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
static struct node *get_last_node(struct linklist *plink);
int insert_at_head(struct linklist *plink,struct node *pnew)
{
	struct node *plast = NULL;

	if(NULL == plink || NULL == pnew)
	{
		printf("Input param is invalid,in %s at %d\n",__FILE__,__LINE__);
		return -1;
	}
	plast = get_last_node(plink);
	if(plast != NULL)
	{
		pnew->pnext = plink->pfirst;
		plast->pnext = pnew;
	}
	else
	{
		pnew->pnext = pnew;
	}
	plink->pfirst = pnew;

	plink->len++;

	return 0;
}

/*获取带头节点的单向循环链表的最后一个节点的地址*/
static struct node *get_last_node(struct linklist *plink)
{
	struct node *plast = NULL;

	plast = plink->pfirst;
	while(plast != NULL)
	{
		if(plast->pnext == plink->pfirst)
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
		pnew->pnext = plink->pfirst;
	}
	else
	{//原表为空表
		plink->pfirst = pnew;
		pnew->pnext = pnew;
	}

	plink->len++;

	return 0;
}

static int is_in_linklist(struct linklist *plink,struct node *pnode)
{
	struct node *pt = NULL;

	if(plink->pfirst == NULL)
	{
		return 0;
	}

	if(pnode == plink->pfirst)
	{
		return 1;
	}

	pt = plink->pfirst->pnext;
	while(pt != plink->pfirst)
	{
		if(pt == pnode)
		{
			break;
		}

		pt = pt->pnext;
	}

	return pnode == pt ? 1 : 0;
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
	struct node *plast = NULL;

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
	plast = get_last_node(plink);

	if(plast != ptemp)
	{
		plink->pfirst = ptemp->pnext;
		plast->pnext = ptemp->pnext;
	}
	else
	{
		plink->pfirst = NULL;
	}

	ptemp->pnext = NULL;

	plink->len--;

	return ptemp;
}

static struct node *get_beforelast_node(struct linklist *plink)
{
	struct node *pbefore = NULL;
	struct node *plast = NULL;


	pbefore = plink->pfirst;
	plast = plink->pfirst;

	while(plast->pnext != plink->pfirst)
	{
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
	plast = pbeforelast->pnext;

	if(plast != pbeforelast)
	{
		pbeforelast->pnext = plast->pnext;
	}
	else
	{
		plink->pfirst = NULL;
	}

	plast->pnext = NULL;

	plink->len--;

	return plast;
}

static struct node *get_before_node(struct linklist *plink,struct node *pnode)
{
	struct node *ptemp = NULL;

	if(plink->pfirst == NULL)
	{
		return NULL;//原表是空表
	}

	ptemp = plink->pfirst;
	if(pnode == ptemp)
	{
		return pnode;
	}

	while(ptemp->pnext != pnode)
	{
		ptemp = ptemp->pnext;
		if(ptemp == plink->pfirst)
		{
			break;
		}
	}
	if(ptemp == plink->pfirst)
	{
		return NULL;//pnode不是链表中的节点
	}

	return ptemp;
}

//移除指定节点
int remove_a_node(struct linklist *plink,struct node *pnode)
{
	struct node *pbefore = NULL;

	if(NULL == plink || NULL == pnode)
	{
		printf("Input param is invalid,in %s at %d\n",__FILE__,__LINE__);
		return -1;
	}

	/*获取指定节点前一个节点的地址*/
	pbefore = get_before_node(plink,pnode);
	if(pbefore == NULL)
	{
		printf("Linklist is empty or Node is not in linklist,remove_a_node failed,%s:%d\n",__FILE__,__LINE__);
		return -1;
	}


	if(pnode != plink->pfirst)
	{
		pbefore->pnext = pnode->pnext;
		pnode->pnext = NULL;
		plink->len--;
	}
	else
	{
		remove_at_head(plink);
	}
	return 0;
}


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
	int isfind = 0;

	pt = plink->pfirst;
	do
	{
		if(strcmp(name,pt->data.name) == 0)
		{
			isfind = 1;
			break;
		}
		pt = pt->pnext;
	}while(pt != plink->pfirst);

	if(isfind)
	{
		return pt;
	}
	else
	{
		return NULL;
	}

}

//排序
//
//int sort_by_phone(struct linklist *plink);

//打印所有联系人
int print_all_person(struct linklist *plink)
{
	struct node *pnode = NULL;

	printf("%-20s%-4s%-20s%-s\n","Name","Sex","Phone","Address");

	pnode = plink->pfirst;
	do
	{
		printf("%-20s%-4c%-20s%-s\n",
		       pnode->data.name,
		       pnode->data.sex,
		       pnode->data.phone,
		       pnode->data.address
		      );
		pnode = pnode->pnext;
	}while(pnode != plink->pfirst);
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

