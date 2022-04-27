#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#define MY_FIFO_NAME "/tmp/myfifo"
int main(int argc,char *argv[])
{
	int ret = 0;
	int wfd = -1;
	int arr[10] = {0};

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
	{
		int i = 0;

		for(i = 0;i < 10;i++)
		{
			arr[i] = rand() % 100;
		}
	}

	write(wfd,arr,10 * sizeof(int));

	close(wfd);
	wfd = -1;

	return 0;
}
