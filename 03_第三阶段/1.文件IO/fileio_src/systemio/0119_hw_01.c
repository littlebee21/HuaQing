/*
 *判断指定文件（main函数参数传入）是否存在并有写权限，
       如果不存在或者没有写权限，则输出“It is not exist or can not be modified!”
       如果存在并有写权限，
		再判断其是不是普通文件，如果是普通文件则在文件尾追加写入一个字符串(用户输入)，
       		如果不是普通文件则输出"It is not regular file"
 *
 * */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *mygets(char *pout,int size);
int input_string(char *pout,int cnt);
int main(int argc,char *argv[])
{
	struct stat meta = {0};
	char buf[40] = "";
	int fd = -1;

	if(argc < 2)
	{
		printf("The argument is too few,Usage:./isexist file\n");
		return 1;
	}

	if(!access(argv[1],F_OK | W_OK))
	{
		stat(argv[1],&meta);
		if((meta.st_mode & S_IFMT) == S_IFREG)
		{
			int len = 0;
			int ret = 0;
			input_string(buf,40);
			fd = open(argv[1],O_WRONLY | O_APPEND);
			if(fd < 0)
			{
				printf("wronly-open %s failed\n",argv[1]);
				return 2;
			}
			
			len = strlen(buf);
			ret = write(fd,buf,len);
			close(fd);
			fd = -1;
			if(ret != len)
			{
				printf("write %s failed,ret=%d\n",buf,ret);
				return 3;
			}
		}
		else
		{
			printf("The %s file is not regular file\n",argv[1]);
		}	
	}
	else
	{
		printf("The %s file is not exist or can not be modified\n",argv[1]);
	}

	return 0;
}

int input_string(char *pout,int cnt)
{
	printf("Please input a string:\n");
	mygets(pout,cnt);

	return 0;
}
