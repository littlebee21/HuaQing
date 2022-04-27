#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include <stdio.h>

#define FILE_NAME "./test.txt"
int main(int argc,char *argv[])
{
	int fd = -1;
	char *p = NULL;
	struct stat meta = {0};
	int ret = 0;
	
	ret = stat(FILE_NAME,&meta);
	if(ret != 0)
	{
		printf("Get %s meta failed\n",FILE_NAME);
		return 1;
	}

	fd = open(FILE_NAME,O_RDWR);
	if(fd < 0)
	{
		printf("rdwr-open %s failed\n",FILE_NAME);
		return 2;
	}

	p = (char *)mmap(NULL,meta.st_size,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
	if(NULL == p)
	{
		printf("mmap %s failed\n",FILE_NAME);
		close(fd);
		fd = -1;
		return 3;
	}

	*(p+1) = 'G';

	msync(p,meta.st_size,MS_SYNC);
	
	munmap(p,meta.st_size);
	p = NULL;

	close(fd);
	fd = -1;
	return 0;
}
