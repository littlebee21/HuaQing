#include "avepdu.h"

int input_count();
int main(int argc,char *argv[])
{
	int ret = 0;
	int wfd = -1;
	int n = 0;
	struct avepdu *pdu = NULL;

	if(0 != access(MY_FIFO_NAME,F_OK))
	{
		ret = mkfifo(MY_FIFO_NAME,0666);
		if(ret < 0)
		{
			printf("mkfifo failed\n");
			return 1;
		}
	}

	wfd = open(MY_FIFO_NAME,O_WRONLY);
	if(wfd < 0)
	{
		unlink(MY_FIFO_NAME);
		printf("open %s failed\n",MY_FIFO_NAME);
		return 2;
	}

	srand(time(NULL));

	while(1)
	{
		/*用户输入随机数个数n*/
		n = input_count();

		/*如果n <= 0则break*/
		if(n <= 0)
		{
			break;
		}

		/*创建pdu*/
		pdu = create_avepdu(n);
		if(NULL == pdu)
		{
			printf("call create_avepdu failed\n");
			break;
		}

		/*发送pdu*/
		ret = send_avepdu(wfd,pdu);
		/*销毁pdu*/
		destroy_avepdu(pdu);
		pdu = NULL;

		if(ret != 0)
		{
			printf("call send_avepdu failed\n");
			break;
		}
	}


	close(wfd);
	wfd = -1;

	return 0;
}

int input_count()
{
	int cnt = 0;

	printf("Please input a number:\n");
	scanf("%d",&cnt);

	while(getchar() != '\n')
	{
	}

	return cnt;
}
