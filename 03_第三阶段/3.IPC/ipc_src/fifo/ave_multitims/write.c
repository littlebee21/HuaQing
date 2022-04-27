#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#define MY_FIFO_NAME "/tmp/myfifo"

int input_count();
int main(int argc,char *argv[])
{
	int ret = 0;
	int wfd = -1;
	int i = 0;
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

		/*分配可以存放n个随机数的空间*/
		prand = (int *)malloc(n *sizeof(int));
		if(NULL == prand)
		{
			perror("Malloc failed in write-process:");
			break;
		}
		memset(prand,0,n * sizeof(int));

		/*产生n个随机数*/
		for(i = 0;i < n;i++)
		{
			*(prand+i) = rand() % 100;
		}

		/*发送n*/
		ret = write(wfd,&n,sizeof(int));
		if(ret != sizeof(int))
		{
			free(prand);
			prand = NULL;
			perror("write n failed:");
			break;
		}

		/*发送n个随机数*/
		ret = write(wfd,prand,n * sizeof(int));
		if(ret != n * sizeof(int))
		{
			free(prand);
			prand = NULL;
			perror("write n-rand failed:");
			break;
		}

		/*释放动态分配的空间*/
		free(prand);
		prand = NULL;
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
