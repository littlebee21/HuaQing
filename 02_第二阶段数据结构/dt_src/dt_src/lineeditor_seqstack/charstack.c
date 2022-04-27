#include "charstack.h"

struct charstack *create_charstack(int maxsize)
{
	struct charstack *pst = NULL;

	pst = (struct charstack *)malloc(sizeof(struct charstack));
	if(NULL == pst)
	{
		printf("Malloc Failed,in %s at %d\n",__FILE__,__LINE__);
		return NULL;
	}
	memset(pst,0, sizeof(struct charstack));

	pst->pt = (T *)malloc(maxsize * sizeof(T));
	if(NULL == pst->pt)
	{
		free(pst);
		pst = NULL;
		printf("Malloc Failed,in %s at %d\n",__FILE__,__LINE__);
		return NULL;
	}
	memset(pst->pt,0,maxsize * sizeof(T));

	pst->max = maxsize;

	return pst;
}

int destroy_charstack(struct charstack *pstack)
{
	if(pstack != NULL)
	{
		if(pstack->pt != NULL)
		{
			free(pstack->pt);
			pstack->pt = NULL;
		}
		free(pstack);
		pstack = NULL;
	}

	return 0;
}

int is_empty_charstack(struct charstack *pstack)
{
	return pstack->top <= 0 ? 1 : 0;
}

int is_full_charstack(struct charstack *pstack)
{
	return pstack->top >= pstack->max ? 1 : 0;
}


int clear_charstack(struct charstack *pstack)
{
	pstack->top = 0;
	memset(pstack->pt,0,pstack->max * sizeof(T));

	return 0;
}

int push_charstack( struct charstack *pstack,T c)
{
	if(is_full_charstack(pstack))
	{
		printf("The charstack is full already,%s:%d\n",__FILE__,__LINE__);
		return -1;
	}
	*(pstack->pt + pstack->top) = c;
	pstack->top++;

	return 0;
}

/*出栈成功返回被删除元素的ASCII码值，失败返回-1*/
int pop_charstack( struct charstack *pstack)
{
	int ret = 0;

	if(is_empty_charstack(pstack))
	{
		printf("The charstack is empty already,%s:%d\n",__FILE__,__LINE__);
		return -1;
	}

	ret = *(pstack->pt + pstack->top - 1);
	pstack->top--;

	return ret;
}

int print_charstack(struct charstack *pstack)
{
	int i = 0;
	for(i = 0;i < pstack->top;i++)
	{
		putchar(*(pstack->pt + i));
	}
	putchar('\n');

	return 0;
}


