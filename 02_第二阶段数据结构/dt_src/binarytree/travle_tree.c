
#include <stdio.h>

typedef char T;

struct treenode
{
	T data;

	struct treenode *lchild;
	struct treenode *rchild;
};

int pre_order(struct treenode *proot);
int main(int argc,char *argv[])
{
	struct treenode node_a = {'A'};
	struct treenode node_b = {'B'};
	struct treenode node_c = {'C'};
	struct treenode node_d = {'D'};
	struct treenode node_e = {'E'};
	struct treenode node_f = {'F'};
	struct treenode node_g = {'G'};
	struct treenode node_h = {'H'};
	struct treenode node_i = {'I'};
	struct treenode node_j = {'J'};

	node_a.lchild = &node_b;
	node_a.rchild = &node_c;

	node_b.lchild = &node_d;
	node_b.rchild = &node_e;

	node_e.lchild = &node_f;
	node_e.rchild = &node_g;

	node_c.rchild = &node_h;
	
	node_h.lchild = &node_i;
	node_h.rchild = &node_j;

	printf("The pre-order ouput is:\n");
	pre_order(&node_a);
	printf("\n");
	return 0;
}

int pre_order(struct treenode *proot)
{
	if(proot == NULL)
	{
		return 0;
	}

	putchar(proot->data);

	pre_order(proot->lchild);
	pre_order(proot->rchild);

	return 0;
}
