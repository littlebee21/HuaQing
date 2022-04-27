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

	pthread_rwlock_init(&pll->rwlock,NULL);
	return pll;
}

int set_exit(struct linklist *plink,int isexit)
{
	pthread_rwlock_wrlock(&plink->rwlock);
	plink->isexit = isexit;
	pthread_rwlock_unlock(&plink->rwlock);

	return 0;
}

int get_exit(struct linklist *plink)
{
	int isexit = 0;

	pthread_rwlock_rdlock(&plink->rwlock);
	isexit = plink->isexit;
	pthread_rwlock_unlock(&plink->rwlock);

	return isexit;
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
		pthread_rwlock_wrlock(&plink->rwlock);
		clear_linklist(plink);
		pthread_rwlock_unlock(&plink->rwlock);
		pthread_rwlock_destroy(&plink->rwlock);
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

//判空
int is_empty_linklist(struct linklist *plink)
{
	return plink->len <= 0 ? 1 : 0;
}


//插入
//头插：新节点插入链表，作为链表中的第一节点
int insert_at_head(struct linklist *plink,struct node *pnew)
{
	pthread_rwlock_wrlock(&plink->rwlock);
	if(NULL == plink || NULL == pnew)
	{
		pthread_rwlock_unlock(&plink->rwlock);
		printf("Input param is invalid,in %s at %d\n",__FILE__,__LINE__);
		return -1;
	}
	pnew->pnext = plink->pfirst;
	plink->pfirst = pnew;

	plink->len++;
	pthread_rwlock_unlock(&plink->rwlock);

	return 0;
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

static struct node * remove_at_head(struct linklist *plink)
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


//移除指定节点
int remove_a_node(struct linklist *plink,struct node *pnode)
{
	struct node *pbefore = NULL;

	pthread_rwlock_wrlock(&plink->rwlock);
	if(NULL == plink || NULL == pnode)
	{
		pthread_rwlock_unlock(&plink->rwlock);
		printf("Input param is invalid,in %s at %d\n",__FILE__,__LINE__);
		return -1;
	}
	if(is_empty_linklist(plink))
	{
		pthread_rwlock_unlock(&plink->rwlock);
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
			pthread_rwlock_unlock(&plink->rwlock);
			return 0;
		}
		else
		{//指定节点不是链表中的节点，不能完成移除
			pthread_rwlock_unlock(&plink->rwlock);
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
	pthread_rwlock_unlock(&plink->rwlock);
	return 0;
}

//查找：
struct node * search_by_name(struct linklist *plink,char *name)
{
	struct node *pt = NULL;

	pthread_rwlock_rdlock(&plink->rwlock);
	pt = plink->pfirst;
	while(pt != NULL)
	{
		if(strcmp(name,pt->data.name) == 0)
		{
			break;
		}

		pt = pt->pnext;
	}
	pthread_rwlock_unlock(&plink->rwlock);

	return pt;
}

//打印所有联系人
int print_all_person(struct linklist *plink)
{
	struct node *pnode = NULL;

	printf("%-20s%-4s%-20s%-s\n","Name","Sex","Phone","Address");

	pthread_rwlock_rdlock(&plink->rwlock);
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
	pthread_rwlock_unlock(&plink->rwlock);
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

