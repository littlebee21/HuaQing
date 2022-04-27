#include "intqueue.h"

struct bankqueue *create_bankqueue(int maxsize)
{
	struct bankqueue *pbq = NULL;

	pbq = (struct bankqueue *)malloc(sizeof(struct bankqueue));
	if(NULL == pbq)
	{
		printf("Malloc failed,%s:%d\n",__FILE__,__LINE__);
		return NULL;
	}
	memset(pbq,0, sizeof(struct bankqueue));

	pbq->max = maxsize;
	pbq->pt = (T *)malloc(maxsize * sizeof(T));
	if(NULL == pbq->pt)
	{
		free(pbq);
		pbq = NULL;
		printf("Malloc failed,%s:%d\n",__FILE__,__LINE__);
		return NULL;
	}
	memset(pbq->pt,0,maxsize * sizeof(T));

	return pbq;
}

int destroy_bankqueue(struct bankqueue *pq)
{
	if(pq != NULL)
	{
		if(pq->pt != NULL)
		{
			free(pq->pt);
			pq->pt = NULL;
		}
		free(pq);
		pq = NULL;
	}

	return 0;
}


int is_empty_bankqueue(struct bankqueue *pq)
{
	return pq->cnt == 0 ? 1 : 0;
}

int is_full_bankqueue(struct bankqueue *pq)
{
	return pq->cnt == pq->max ? 1 : 0;
}


//如果sizeof(T)小于等于平台字长，入队函数的第二个参数可直接用T类型
//如果sizeof(T)大于平台字长，入队函数的第二个参数则用T*类型
int intnode_enqueue(struct bankqueue *pq,T ele)
{
	if(is_full_bankqueue(pq))
	{
		printf("The queue is full,enqueue failed,%s:%d\n",__FILE__,__LINE__);
		return -1;
	}
	memcpy(pq->pt + pq->tail,&ele,sizeof(T));
	pq->tail = (pq->tail + 1) % pq->max;

	pq->cnt++;

	return 0;
}


int intnode_dequeue(struct bankqueue *pq,T *pout)
{
	if(is_empty_bankqueue(pq))
	{
		printf("The queue is empty,dequeue failed,%s:%d\n",__FILE__,__LINE__);
		return -1;
	}

	memcpy(pout,pq->pt + pq->head,sizeof(T));

	pq->head = (pq->head + 1) % pq->max;

	pq->cnt--;

	return 0;
}


int get_bankqueue_len(struct bankqueue *pq)
{
	return pq->cnt;
}

