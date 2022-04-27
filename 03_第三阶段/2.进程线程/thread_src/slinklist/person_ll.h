#ifndef PERSON_LINKLIST_H
#define PERSON_LINKLIST_H

#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>

#define NAME_LEN 20
#define PHONE_LEN 20
#define ADDR_LEN 64
struct person
{
	char name[NAME_LEN];
	char sex;
	char phone[PHONE_LEN];
	char address[ADDR_LEN];
};
typedef struct person T;

struct node
{
	T data;

	struct node *pnext;
};

struct linklist
{
	int len;
	struct node *pfirst;

	int isexit;//0 not exit  1 exit
	pthread_rwlock_t rwlock;
};

int set_exit(struct linklist *plink,int isexit);
int get_exit(struct linklist *plink);

//建表：给引擎对象分配空间
struct linklist *create_linklist();

//清空表：将所有节点空间释放，置头节点的len成员为0，pfirst成员为NULL
int clear_linklist(struct linklist *plink);

//删表：先清空表，然后再释放头节点的空间
int destroy_linklist(struct linklist *plink);

//创建一个节点
struct node *create_node(T *pdata);

//销毁一个节点：释放节点占用的内存空间
int destroy_node(struct node *pnode);

//判空
int is_empty_linklist(struct linklist *plink);

//插入
//头插：新节点插入链表，作为链表中的第一节点
int insert_at_head(struct linklist *plink,struct node *pnew);


//移除指定节点
int remove_a_node(struct linklist *plink,struct node *pnode);

//查找：
struct node * search_by_name(struct linklist *plink,char *name);

//打印所有联系人
int print_all_person(struct linklist *plink);

//打印一个联系人
int print_a_person(struct node *pnode);

#endif
