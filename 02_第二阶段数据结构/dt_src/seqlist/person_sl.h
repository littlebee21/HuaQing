#ifndef PERSON_SEQLIST_H
#define PERSON_SEQLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 20
#define PHONE_LEN 16
#define ADDR_LEN 64
struct person
{
	char name[NAME_LEN];
	char sex;
	char phone[PHONE_LEN];
	char address[ADDR_LEN];
};
typedef struct person T;


struct seqlist
{
	T *pt;//指向空间为连续顺序存放T类型元素的数组空间
	int max;//表容量，pt指向空间最多可以存放的元素数目
	int len;//表长，记录从下标零开始连续元素的个数
};

//建表：给引擎对象和存放批量元素的数组分配空间
struct seqlist *create_seqlist(int maxsize);

//清空表：
int clear_seqlist(struct seqlist *pseq);

//删表：释放引擎对象和存放批量元素的数组空间
int destroy_seqlist(struct seqlist *pseq);

//求表长
int get_seqlist_len(struct seqlist *pseq);

//判空
int is_empty_seqlist(struct seqlist *pseq);

//判满
int is_full_seqlist(struct seqlist *pseq);

//插入
//头插：新元素插入在下标最小的位置
int insert_at_head(struct seqlist *pseq,T *pnew);

//尾插：新元素插入在len的位置
int insert_at_tail(struct seqlist *pseq,T *pnew);

//在指定下标位置插入:
int insert_at_location(struct seqlist *pseq,T *pnew,int loc);

//删除
//头删：删除下标最小的元素
int delete_at_head(struct seqlist *pseq);

//尾删：删除下标为len-1的元素
int delete_at_tail(struct seqlist *pseq);

//删除指定下标位置的元素：
int delete_at_location(struct seqlist *pseq,int loc);

//修改:
int modify(struct seqlist *pseq,int loc,T *pdata);

//查找：
int search_by_name(struct seqlist *pseq,char *name);

//排序
int sort_by_phone(struct seqlist *pseq);

//打印所有联系人
int print_all_person(struct seqlist *pseq);

//打印一个联系人
int print_a_person(T *);

#endif
