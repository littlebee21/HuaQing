#include "person_dll.h"

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

	if(plink->pfirst != NULL)
	{
		plink->pfirst->pprev = pnew;
	}
	//else ---- 此步无需任何操作
	
	plink->pfirst = pnew;
	pnew->pprev = NULL;

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
	pnew->pprev = plast;
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
	pnew->pprev = pnode;

	if(pnode->pnext != NULL)
	{
		pnode->pnext->pprev = pnew;
	}
	//else --- 此步无需任何操作
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

	if(ptemp->pnext != NULL)
	{
		ptemp->pnext->pprev = NULL;
	}
	//else 原表中仅有一个节点时，此步无需任何操作

	ptemp->pnext = NULL;

	plink->len--;

	return ptemp;
}

//尾移除：将最后一个节点脱链
struct node * remove_at_tail(struct linklist *plink)
{
	struct node *plast = NULL;

	if(NULL == plink)
	{
		printf("Input param is invalid,in %s at %d\n",__FILE__,__LINE__);
		return NULL;
	}

	plast = get_last_node(plink);
	if(NULL == plast)
	{//原表为空表
		printf("The linklist is empty already,remove_at_head failed,in %s at %d\n",__FILE__,__LINE__);
		return NULL;
	}

	if(plast->pprev != NULL)
	{
		plast->pprev->pnext = NULL;
	}
	else
	{//原表中仅有一个节点
		plink->pfirst = NULL;
	}

	plast->pprev = NULL;

	plink->len--;

	return plast;
}

//移除指定节点
int remove_a_node(struct linklist *plink,struct node *pnode)
{
	if(NULL == plink || NULL == pnode)
	{
		printf("Input param is invalid,in %s at %d\n",__FILE__,__LINE__);
		return -1;
	}
	if(!is_in_linklist(plink,pnode))
	{
		printf("The node is not in linklist ,remove_a_node failed,in %s at %d\n",__FILE__,__LINE__);
		return -1;
	}

	if(pnode->pprev != NULL)
	{
		pnode->pprev->pnext = pnode->pnext;
	}
	else
	{//pnode指向的节点为第一节点
		plink->pfirst = pnode->pnext;
	}

	if(pnode->pnext != NULL)
	{
		pnode->pnext->pprev = pnode->pprev;
	}
	//else pnode指向的节点为最后一个节点，此步无需任何操作

	pnode->pnext = NULL;

	pnode->pprev = NULL;

	plink->len--;
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

//排序
//
//int sort_by_phone(struct linklist *plink);

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

