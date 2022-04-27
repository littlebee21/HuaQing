#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#define MY_FIFO_NAME "/tmp/myfifo"
float get_ave(int *pi,int cnt);
int main(int argc,char *argv[])
{
	int ret = 0;
	int rfd = -1;
	int arr[10] = {};

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

	read(rfd,arr,10 * sizeof(int));
	printf("The average is %.2f\n",get_ave(arr,10));


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
