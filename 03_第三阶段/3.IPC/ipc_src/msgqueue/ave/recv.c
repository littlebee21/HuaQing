#include "mymsg.h"

float get_ave(int *pi,int cnt);

int main(int argc,char *argv[])
{
	int mqid = -1;
	key_t mqkey;
	struct mymsg *pmsg = NULL;

	mqkey = ftok("./send.c",1);

	mqid = msgget(mqkey,IPC_CREAT | 0666);
	if(mqid < 0)
	{
		printf("msgget failed\n");
		return 1;
	}

	pmsg = recv_mymsg(mqid,99);
	if(pmsg != NULL)
	{
		printf("The ave is %.2f\n",get_ave(pmsg->data,pmsg->len / sizeof(int)));
		destroy_mymsg(pmsg);
		pmsg = NULL;
	}
	else
	{
		printf("call recv_mymsg failed\n");
	}

	return 0;
}

float get_ave(int *pi,int cnt)
{
        float sum = 0.0f;
        int i = 0;

        for(i = 0;i < cnt;i++)
        {
                sum += *(pi+i);
        }

        return sum / cnt;
}

