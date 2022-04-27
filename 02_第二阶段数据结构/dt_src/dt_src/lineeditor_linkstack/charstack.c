#include "charstack.h"

struct charstack *create_charstack()
{
	struct charstack *pnew = NULL;

	pnew = (struct charstack *)malloc(sizeof(struct charstack));
	if(NULL == pnew)
	{
		printf("Malloc failed,%s:%d\n",__FILE__,__LINE__);
		return NULL;
	}
	memset(pnew,0,sizeof(struct charstack));

	return pnew;
}

int clear_charstack(struct charstack *pstack)
{
	struct charnode *ptemp =NULL;
	struct charnode *pnext =NULL;

	ptemp = pstack->ptop;
	while(ptemp != NULL)
	{
		pnext = ptemp->pnext;
		destroy_charnode(ptemp);
		ptemp = pnext;
	}

	pstack->ptop = NULL;
	pstack->len = 0;

	return 0;
}

int destroy_charstack(struct charstack *pstack)
{
	if(pstack != NULL)
	{
		clear_charstack(pstack);
		free(pstack);
		pstack = NULL;
	}

	return 0;
}

struct charnode *create_charnode(char ch)
{
	struct charnode *pnew = NULL;

	pnew = (struct charnode *)malloc(sizeof(struct charnode));
	if(NULL == pnew)
	{
		printf("Malloc failed,%s:%d\n",__FILE__,__LINE__);
		return NULL;
	}
	memset(pnew,0,sizeof(struct charnode));

	pnew->ch = ch;
	return pnew;
}

int destroy_charnode(struct charnode *pnode)
{
	if(pnode != NULL)
	{
		free(pnode);
		pnode = NULL;
	}
	return 0;
}

int is_empty_charstack(struct charstack *pstack)
{
	return pstack->ptop == NULL ? 1 : 0;
}


int push_charstack(struct charstack *pstack,struct charnode *pnew)
{
	pnew->pnext = pstack->ptop;
	pstack->ptop = pnew;

	pstack->len++;
	return 0;
}


struct charnode *pop_charstack( struct charstack *pstack)
{
	struct charnode *pfirst = NULL;

	pfirst = pstack->ptop;
	pstack->ptop = pfirst->pnext;

	pfirst->pnext = NULL;

	pstack->len--;

	return pfirst;
}

#define USING_CHARARR

#ifndef USING_CHARARR
static int print_charstack_private(struct charnode *pnode)
{
	if(pnode == NULL)
	{
		return 0;
	}

	print_charstack_private(pnode->pnext);
	putchar(pnode->ch);

	return 0;
}
#endif
int print_charstack(struct charstack *pstack)
{
#ifdef USING_CHARARR
	int i = 0;
	struct charnode *pt = NULL;
	/*
	char pbuf[pstack->len+1];//C99语法，不通用，栈区
				//所有平台都支持标准C（C89、C88），某些高端场合是支持C99
				//linux内核程序的C语言标准 = C99 + GNU组织的C扩展
	
	memset(pbuf,0,pstack->len + 1);
	*/
	
	char *pbuf = NULL;

	pbuf = (char *)malloc(pstack->len + 1);
	if(NULL == pbuf)
	{
		printf("Malloc Failed,%s:%d\n",__FILE__,__LINE__);
		return -1;
	}
	memset(pbuf,0,pstack->len + 1);


	for(pt = pstack->ptop,i = pstack->len-1;i >= 0;i--,pt=pt->pnext)
	{
		*(pbuf+i) = pt->ch;
	}

	printf("%s\n",pbuf);

	free(pbuf);
	pbuf = NULL;

	return 0;
#else
	struct charnode *pnode = pstack->ptop;

	print_charstack_private(pnode);
	printf("\n");
	return 0;
#endif
}



