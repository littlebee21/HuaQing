#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MY_FIFO_NAME "/tmp/myfifo"
float get_ave(int *pi,int cnt);
int main(int argc,char *argv[])
{
	int ret = 0;
	int rfd = -1;
	int n = 0;
	int *prand = NULL;

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
		/*先收4个字节的一个整数n（后续将要接收的随机数的个数）*/
		ret = read(rfd,&n,sizeof(int));
		if(ret < 0)
		{
			perror("read n failed:");
			break;
		}
		else if(ret == 0)//写端描述符已关闭
		{
			printf("read-process will exit\n");
			break;
		}
		else if(ret != sizeof(int))
		{
			printf("read bytes is error\n");
			break;
		}

		if(n <= 0)
		{
			printf("n is not valid\n");
			break;
		}

		/*分配可以存放n个随机数的内存空间*/
		prand = (int *)malloc(n * sizeof(int));
		if(NULL == prand)
		{
			printf("Malloc failed in read-process\n");
			break;
		}
		memset(prand,0,n * sizeof(int));

		/*再接收n个随机数*/
		ret = read(rfd,prand,n * sizeof(int));
		if(ret != n * sizeof(int))
		{
			free(prand);
			prand = NULL;
			printf("read %d-rands failed,ret=%d\n",n,ret);
			break;
		}

		/*计算均值并输出*/
		printf("The ave is %.2f\n",get_ave(prand,n));

		/*释放动态分配的空间*/
		free(prand);
		prand = NULL;
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
