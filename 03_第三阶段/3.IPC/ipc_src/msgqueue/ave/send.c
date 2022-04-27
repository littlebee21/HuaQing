#include "mymsg.h"

int main(int argc,char *argv[])
{
	int mqid = -1;
	key_t mqkey;
	int ret = 0;
	struct mymsg *pmsg = NULL;

	srand(time(NULL));

	mqkey = ftok("./send.c",1);

	mqid = msgget(mqkey,IPC_CREAT | 0666);
	if(mqid < 0)
	{
		printf("msgget failed\n");
		return 1;
	}

	pmsg = create_mymsg(10,99);
	ret = send_mymsg(mqid,pmsg);
	destroy_mymsg(pmsg);
	pmsg = NULL;
	if(ret < 0)
	{
		printf("call send_mymsg failed\n");
		return 2;
	}
	

	return 0;
}
