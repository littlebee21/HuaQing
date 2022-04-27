#ifndef MY_MSG_H
#define MY_MSG_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <stdio.h>

struct mymsg
{
	long type;
	char buf[20];
};




#endif
