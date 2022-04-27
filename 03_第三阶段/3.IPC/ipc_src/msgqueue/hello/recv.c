#include "mymsg.h"

int main(int argc,char *argv[])
{
	int mqid = -1;
	key_t mqkey;
	int ret = 0;
	struct mymsg msg = {0};

	mqkey = ftok("./send.c",1);

	mqid = msgget(mqkey,IPC_CREAT | 0666);
	if(mqid < 0)
	{
		printf("msgget failed\n");
		return 1;
	}

	ret = msgrcv(mqid,&msg,6,0,0);
	if(ret < 0)
	{
		printf("recv msg failed\n");
		return 2;
	}
	
	printf("msg is %s\n",msg.buf);

	return 0;
}
