#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdio.h>

int main(int argc,char *argv[])
{
	struct stat st = {0};
	int ret = 0;

	if(argc < 2)
	{
		printf("The argument is too few,Usage:./getfilesize file\n");
		return 1;
	}

	ret = stat(argv[1],&st);
	if(ret < 0)
	{
		printf("get %s stat failed\n",argv[1]);
		return 2;
	}

	if((st.st_mode & S_IFMT) == S_IFREG)
	{
		printf("The size of %s is %ld\n",argv[1],st.st_size);
	}
	else
	{
		printf("The %s file is not regular file\n",argv[1]);
	}
	return 0;
}
