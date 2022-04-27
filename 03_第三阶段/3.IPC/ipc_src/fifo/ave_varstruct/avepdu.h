#ifndef AVE_PDU_H
#define AVE_PDU_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

#define MY_FIFO_NAME "/tmp/myfifo"

/*
 *变长结构体:var-struct
 *1. 最后一个成员是长度为1的数组类型（数组名单独出现代表下标为0的元素的首地址）
     该成员名就是最后一个成员开始后续空间的首地址
 *2. 用变长结构体定义变量、数组或作为其它结果体成员类型是没有意义的，因此项目中仅用其指针类型
 *
 * */
struct avepdu
{
	int n;
	int rands[1];
};


struct avepdu *create_avepdu(int cnt);
int destroy_avepdu(struct avepdu *p_pdu);

int send_avepdu(int fd,struct avepdu *p_pdu);
struct avepdu *recv_avepdu(int fd);






#endif
