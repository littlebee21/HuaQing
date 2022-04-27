#ifndef CHAR_STACK_H
#define CHAR_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char T;

struct charstack
{
	T *pt;
	int max;
	int top;//表示栈顶下标，其实也是表长
};

struct charstack *create_charstack(int maxsize);
int destroy_charstack(struct charstack *pstack);

int is_empty_charstack(struct charstack *pstack);
int is_full_charstack(struct charstack *pstack);

int clear_charstack(struct charstack *pstack);

int push_charstack( struct charstack *pstack,T c);

/*出栈成功返回被删除元素的ASCII码值，失败返回-1*/
int pop_charstack( struct charstack *pstack);

int print_charstack(struct charstack *pstack);


#endif
