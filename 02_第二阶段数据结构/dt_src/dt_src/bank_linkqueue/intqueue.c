#include "intqueue.h"

struct bankqueue *create_bankqueue()
{
	struct bankqueue *pnew = NULL;

	pnew = (struct bankqueue *)malloc(sizeof(struct bankqueue));
	if(NULL == pnew)
	{
		printf("Malloc failed,%s:%d\n",__FILE__,__LINE__);
		return NULL;
	}
	memset(pnew,0,sizeof(struct bankqueue));

	return pnew;
}

int destroy_bankqueue(struct bankqueue *pq)
{
	struct intnode *ptemp = NULL;
	struct intnode *pnext = NULL;

	ptemp = pq->phead;
	while(ptemp != NULL)
	{
		pnext = ptemp->pnext;
		destroy_intnode(ptemp);
		ptemp = pnext;
	}

	free(pq);
	pq = NULL;

	return 0;
}


struct intnode *create_intnode(int num)
{
	struct intnode *pnew = NULL;

	pnew = (struct intnode *)malloc(sizeof(struct intnode));
	if(NULL == pnew)
	{
		printf("Malloc failed,%s:%d\n",__FILE__,__LINE__);
		return NULL;
	}
	memset(pnew,0,sizeof(struct intnode));

	pnew->no = num;

	return pnew;
}

int destroy_intnode(struct intnode *pnode)
{
	if(pnode != NULL)
	{
		free(pnode);
		pnode = NULL;
	}
	return 0;
}


int intnode_enqueue(struct bankqueue *pq,struct intnode *pnew)
{
	struct intnode *plast = NULL;

	plast = pq->ptail;

	if(plast == NULL)
	{//原表为空表
		pq->phead = pnew;
	}
	else
	{//原表为非空表
		plast->pnext = pnew;
	}
	pq->ptail = pnew;
	pnew->pnext = NULL;
	pq->cnt++;

	return 0;
}

struct intnode *intnode_dequeue(struct bankqueue *pq)
{
	struct intnode *pfirst = NULL;

	pfirst = pq->phead;

	if(pfirst != NULL)
	{
		if(pq->phead == pq->ptail)
		{
			pq->ptail = pfirst->pnext;
		}
		pq->phead = pfirst->pnext;
		pfirst->pnext = NULL;

		pq->cnt--;
		return pfirst;
	}
	else
	{
		printf("Dequeue Failed,%s:%d\n",__FILE__,__LINE__);
		return NULL;
	}
}


int get_bankqueue_len(struct bankqueue *pq)
{
	return pq->cnt;
}



