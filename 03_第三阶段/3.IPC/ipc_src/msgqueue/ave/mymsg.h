#ifndef MY_MSG_H
#define MY_MSG_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

#define MAX_COUNT 100

struct mymsg
{
	int len;//data部分的字节数
	long type;
	int data[1];
};


struct mymsg *create_mymsg(int cnt,int type);
int destroy_mymsg(struct mymsg *pmsg);

int send_mymsg(int mqid,struct mymsg *pmsg);
struct mymsg *recv_mymsg(int mqid,int type);



#endif
