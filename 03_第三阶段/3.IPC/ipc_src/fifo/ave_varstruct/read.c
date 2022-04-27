#include "avepdu.h"

float get_ave(int *pi,int cnt);
int main(int argc,char *argv[])
{
	int ret = 0;
	int rfd = -1;
	struct avepdu * pdu = NULL;

	if(0 != access(MY_FIFO_NAME,F_OK))
	{
		ret = mkfifo(MY_FIFO_NAME,0666);
		if(ret < 0)
		{
			printf("mkfifo failed\n");
			return 1;
		}
	}

	rfd = open(MY_FIFO_NAME,O_RDONLY);
	if(rfd < 0)
	{
		unlink(MY_FIFO_NAME);
		printf("open %s failed\n",MY_FIFO_NAME);
		return 2;
	}

	while(1)
	{
		/*接收pdu*/
		pdu = recv_avepdu(rfd);
		if(NULL == pdu)
		{
			printf("call recv_avepdu failed\n");
			break;
		}

		/*计算均值并输出*/
		printf("The ave is %.2f\n",get_ave(pdu->rands,pdu->n));

		/*销毁pdu*/
		destroy_avepdu(pdu);
		pdu = NULL;
	}

	close(rfd);
	rfd = -1;

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
