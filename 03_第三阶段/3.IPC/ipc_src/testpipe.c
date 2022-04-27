#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <stdio.h>

int main(int argc,char *argv[])
{
	int arrfd[2] = {-1.-1};
	int ret = 0;
	pid_t pid;
	
	ret = pipe(arrfd);
	if(ret < 0)
	{
		perror("pipe failed:");
		return 1;
	}

	pid = fork();
	if(pid < 0)
	{
		printf("fork failed\n");
		close(arrfd[0]);
		close(arrfd[1]);
		return 2;
	}

	if(0 == pid)
	{//son-process
		char buf[20] = "";

		/*子进程关闭写端描述符，保留读端描述符*/
		close(arrfd[1]);
		arrfd[1] = -1;

		read(arrfd[0],buf,6);
		printf("buf=%s\n",buf);

		/*子进程不再使用管道读端收数据时*/
		close(arrfd[0]);
		arrfd[0] = -1;
	}
	else
	{//father-process
		/*父进程关闭读端描述符，保留写端描述符*/
		close(arrfd[0]);
		arrfd[0] = -1;

		write(arrfd[1],"hello",6);
		wait(NULL);
		
		/*父进程不再使用管道读端发数据时*/
		close(arrfd[1]);
		arrfd[1] = -1;
	}


	return 0;
}
