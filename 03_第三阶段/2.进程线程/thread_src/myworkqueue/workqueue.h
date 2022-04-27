#ifndef INT_QUEUE_H
#define INT_QUEUE_H

#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>

typedef int T;

struct work
{
	T data;
	int (*handle)(T *pdata);
	struct work *pnext;
};

struct wkqueue
{
	int cnt;

	int isexit;

	struct work *phead;//始终存放链表第一个节点的地址
	struct work *ptail;//始终存放链表最后一个节点的地址

	pthread_cond_t cond;
	pthread_mutex_t lock;
};
struct wkqueue *create_wkqueue();
int destroy_wkqueue(struct wkqueue *pq);

struct work *create_work(T *pdata);
int destroy_work(struct work *pnode);

int work_enqueue(struct wkqueue *pq,struct work *pnew);
struct work *work_dequeue(struct wkqueue *pq);

int set_exit(struct wkqueue *pq,int isexit);
int get_exit(struct wkqueue *pq);

int get_wkqueue_len(struct wkqueue *pq);


#endif
