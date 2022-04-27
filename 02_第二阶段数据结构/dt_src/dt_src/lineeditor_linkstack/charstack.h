#ifndef CHAR_STACK_H
#define CHAR_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char T;

struct charnode
{
	T ch;

	struct charnode *pnext;
};

struct charstack
{
	int len;

	struct  charnode *ptop;//链表第一个节点位置作为栈顶，ptop始终保存第一个节点的地址
};

struct charstack *create_charstack();
int destroy_charstack(struct charstack *pstack);

struct charnode *create_charnode(char ch);
int destroy_charnode(struct charnode *pnode);

int is_empty_charstack(struct charstack *pstack);
//int is_full_charstack(struct charstack *pstack);

int clear_charstack(struct charstack *pstack);

int push_charstack( struct charstack *pstack,struct charnode *pnew);

struct charnode *pop_charstack( struct charstack *pstack);

int print_charstack(struct charstack *pstack);


#endif
