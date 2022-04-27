#ifndef INT_QUEUE_H
#define INT_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int T;

struct intnode
{
	T no;
	struct intnode *pnext;
};

struct bankqueue
{
	int cnt;

	struct intnode *phead;//始终存放链表第一个节点的地址
	struct intnode *ptail;//始终存放链表最后一个节点的地址
};

struct bankqueue *create_bankqueue();
int destroy_bankqueue(struct bankqueue *pq);

struct intnode *create_intnode(int num);
int destroy_intnode(struct intnode *pnode);

int intnode_enqueue(struct bankqueue *pq,struct intnode *pnew);
struct intnode *intnode_dequeue(struct bankqueue *pq);

int get_bankqueue_len(struct bankqueue *pq);


#endif
