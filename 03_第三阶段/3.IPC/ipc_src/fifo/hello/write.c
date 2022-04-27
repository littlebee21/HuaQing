#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#define MY_FIFO_NAME "/tmp/myfifo"
int main(int argc,char *argv[])
{
	int ret = 0;
	int wfd = -1;

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

	write(wfd,"hello",6);

	close(wfd);
	wfd = -1;

	return 0;
}
