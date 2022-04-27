#include "mymsg.h"

int main(int argc,char *argv[])
{
	int mqid = -1;
	key_t mqkey;
	int ret = 0;
	struct mymsg msg = {11,"hello"};

	mqkey = ftok("./send.c",1);

	mqid = msgget(mqkey,IPC_CREAT | 0666);
	if(mqid < 0)
	{
		printf("msgget failed\n");
		return 1;
	}

	ret = msgsnd(mqid,&msg,6,0);
	if(ret < 0)
	{
		printf("send msg failed\n");
		return 2;
	}
	

	return 0;
}
