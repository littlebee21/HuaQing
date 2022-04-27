#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#define FILE_NAME "./test.txt"
void *write_thread(void *arg);
int main(int argc,char *argv[])
{
	pthread_t tid;
	int ret = 0;
	int fd = -1;

	fd = open(FILE_NAME,O_CREAT | O_RDWR | O_TRUNC,0666);
	if(fd < 0)
	{
		printf("rw-open %s failed\n",FILE_NAME);
		return 1;
	}

	ret = pthread_create(&tid,NULL,write_thread,(void *)(long)fd);
	if(ret != 0)
	{
		close(fd);
		fd = -1;
		printf("pthread_create failed\n");
		return 2;
	}

	pthread_join(tid,NULL);

	//read data from file
	{
		char buf[12] = "";

		lseek(fd,0,SEEK_SET);
		read(fd,buf,11);
		printf("read data is %s\n",buf);
	}


	close(fd);
	fd = -1;
	return 0;
}

void *write_thread(void *arg)
{
	int fd = (int)(long)arg;

	//write data into file
	write(fd,"Hello World",11);

	return NULL;
}
