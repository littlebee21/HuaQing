#include "mymsg.h"

struct mymsg *create_mymsg(int cnt,int type)
{
	struct mymsg *pmsg = NULL;
	int len = 0;
	int i = 0;

	len = cnt * sizeof(int) + sizeof(int) + sizeof(long);

	pmsg = (struct mymsg *)malloc(len);
	if(NULL == pmsg)
	{
		printf("malloc failed in create_mymsg\n");
		return NULL;
	}
	memset(pmsg,0,len);

	pmsg->type = type;
	pmsg->len = cnt * sizeof(int);

	for(i = 0;i < cnt;i++)
	{
		*(pmsg->data + i) = rand() % 100;
	}

	return pmsg;
	
}

int destroy_mymsg(struct mymsg *pmsg)
{
	if(pmsg != NULL)
	{
		free(pmsg);
		pmsg = NULL;
	}

	return 0;
}

int send_mymsg(int mqid,struct mymsg *pmsg)
{
	int ret = 0;

	ret = msgsnd(mqid,&pmsg->type,pmsg->len,0);
	if(ret < 0)
	{
		printf("send_mymsg failed,ret=%d\n",ret);
		return -1;
	}

	return 0;
}

struct mymsg *recv_mymsg(int mqid,int type)
{
	struct mymsg *pmsg = NULL;
	int len = 0;
	int ret = 0;

	len = MAX_COUNT * sizeof(int) + sizeof(int) + sizeof(long);

	pmsg = (struct mymsg *)malloc(len);	
	if(NULL == pmsg)
	{
		printf("malloc failed in recv_mymsg\n");
		return NULL;
	}
	memset(pmsg,0,len);

	ret = msgrcv(mqid,&pmsg->type,MAX_COUNT * sizeof(int),type,0);
	if(ret < 0)
	{
		printf("recv mymsg failed,ret=%d\n",ret);
		return NULL;
	}
	pmsg->len = ret;

	return pmsg;
}


