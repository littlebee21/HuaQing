#include "workqueue.h"

struct wkqueue *create_wkqueue()
{
	struct wkqueue *pnew = NULL;

	pnew = (struct wkqueue *)malloc(sizeof(struct wkqueue));
	if(NULL == pnew)
	{
		printf("Malloc failed,%s:%d\n",__FILE__,__LINE__);
		return NULL;
	}
	memset(pnew,0,sizeof(struct wkqueue));

	pthread_cond_init(&pnew->cond,NULL);
	pthread_mutex_init(&pnew->lock,NULL);

	return pnew;
}

int destroy_wkqueue(struct wkqueue *pq)
{
	struct work *ptemp = NULL;
	struct work *pnext = NULL;

	ptemp = pq->phead;
	while(ptemp != NULL)
	{
		pnext = ptemp->pnext;
		destroy_work(ptemp);
		ptemp = pnext;
	}

	pthread_cond_destroy(&pq->cond);
	pthread_mutex_destroy(&pq->lock);
	free(pq);
	pq = NULL;

	return 0;
}

static int handle_work(T *pdata)
{
	printf("Handle %d work\n",*pdata);
	sleep(1);
	return 0;
}

struct work *create_work(T *pdata)
{
	struct work *pnew = NULL;

	pnew = (struct work *)malloc(sizeof(struct work));
	if(NULL == pnew)
	{
		printf("Malloc failed,%s:%d\n",__FILE__,__LINE__);
		return NULL;
	}
	memset(pnew,0,sizeof(struct work));

	memcpy(&pnew->data,pdata,sizeof(T));
	pnew->handle = handle_work;

	return pnew;
}

int destroy_work(struct work *pnode)
{
	if(pnode != NULL)
	{
		free(pnode);
		pnode = NULL;
	}
	return 0;
}


int work_enqueue(struct wkqueue *pq,struct work *pnew)
{
	struct work *plast = NULL;

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

struct work *work_dequeue(struct wkqueue *pq)
{
	struct work *pfirst = NULL;

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

int set_exit(struct wkqueue *pq,int isexit)
{
	pq->isexit = isexit;

	return 0;
}

int get_exit(struct wkqueue *pq)
{
	int isexit = 0;

	isexit = pq->isexit;

	return isexit;
}

int get_wkqueue_len(struct wkqueue *pq)
{
	return pq->cnt;
}



