/*模拟实现命令行界面（仅考虑执行一些无参命令)*/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

char *mygets(char *pout,int size);
int input_cmd(char *pout,int len);

#define CMD_LEN 64

int main(int argc,char *argv[])
{
	pid_t pid;
	char cmdbuf[CMD_LEN] = "";

	while(1)
	{
		input_cmd(cmdbuf,CMD_LEN);
		if(strcmp(cmdbuf,"exit") == 0)
		{
			break;
		}

		pid = fork();
		if(pid < 0)
		{
			printf("fork failed\n");
			break;
		}
		if(pid == 0)
		{
			int ret = 0;
			ret = execlp(cmdbuf,cmdbuf,NULL);
			if(ret < 0)
			{
				printf("The Command is not found\n");
				return 1;
			}
		}
		else
		{
			wait(NULL);
		}
	}

	return 0;
}

int input_cmd(char *pout,int len)
{
	printf("xxx@yyy$");
	mygets(pout,len);

	return 0;
}
