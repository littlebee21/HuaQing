#ifndef INT_QUEUE_H
#define INT_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int T;

struct bankqueue
{
	T *pt;
	int max;//容量：pt指向空间最多存放的元素个数
	int cnt;//表长：pt指向空间当前存放的元素个数
	int tail;//最后一个元素的下标+1 （最后一个元素下标为max-1，时tail为0）
	int head;//第一个元素的下标
};

struct bankqueue *create_bankqueue(int maxsize);
int destroy_bankqueue(struct bankqueue *pq);

int is_empty_bankqueue(struct bankqueue *pq);
int is_full_bankqueue(struct bankqueue *pq);

//如果sizeof(T)小于等于平台字长，入队函数的第二个参数可直接用T类型
//如果sizeof(T)大于平台字长，入队函数的第二个参数则用T*类型
int intnode_enqueue(struct bankqueue *pq,T ele);

int intnode_dequeue(struct bankqueue *pq,T *pout);

int get_bankqueue_len(struct bankqueue *pq);


#endif
