#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#define MY_FIFO_NAME "/tmp/myfifo"
int main(int argc,char *argv[])
{
	int ret = 0;
	int rfd = -1;
	char buf[20] = "";

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

	read(rfd,buf,6);
	printf("buf=%s\n",buf);

	close(rfd);
	rfd = -1;

	return 0;
}
