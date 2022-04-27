#ifndef PERSON_LINKLIST_H
#define PERSON_LINKLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
};

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

//求表长
int get_linklist_len(struct linklist *plink);

//判空
int is_empty_linklist(struct linklist *plink);


//插入
//头插：新节点插入链表，作为链表中的第一节点
int insert_at_head(struct linklist *plink,struct node *pnew);

//尾插：新元素插入链表，作为链表中的最后一个节点
int insert_at_tail(struct linklist *plink,struct node *pnew);

//在指定节点后插入新节点:
int insert_at_after_node(struct linklist *plink,struct node *pnode,struct node *pnew);

//移除
//头移除：将第一个节点脱链
struct node * remove_at_head(struct linklist *plink);

//尾移除：将最后一个节点脱链
struct node * remove_at_tail(struct linklist *plink);

//移除指定节点
//#define USING_SWAP
#ifndef USING_SWAP
int remove_a_node(struct linklist *plink,struct node *pnode);
#else
struct node * remove_a_node(struct linklist *plink,struct node *pnode);
#endif

//修改:
int modify(struct node *pnode,T *pdata);

//查找：
struct node * search_by_name(struct linklist *plink,char *name);

//排序方案1-----硬排 ------ 会改变链表中节点的相互位置
int sort_by_phone(struct linklist *plink);


//排序方案2-----借助存放节点地址的动态数组 ---- 不会改变链表中节点的相互位置
struct node **sort_person_linklist_by_phone(struct linklist *plink);
int print_sort_result(struct node **ppsorted,int cnt);
int free_sort_result(struct node **ppsorted);
//打印所有联系人
int print_all_person(struct linklist *plink);

//打印一个联系人
int print_a_person(struct node *pnode);

#endif
