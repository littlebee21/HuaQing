/*父进程定义一个整型数组，数组元素的值由用户输入，在新建子进程中完成找最大元素，然后在父进程中显示出最大元素及其下标位置*/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <stdio.h>

#define N 10
int input_arr(int *parr,int cnt);
int find_max(int *parr,int cnt);
int main(int argc,char *argv[])
{
	pid_t pid = -1;
	int arr[N] = {0};	

	input_arr(arr,N);

	pid = fork();
	if(pid < 0)
	{
		printf("fork failed\n");
		return 1;
	}

	if(pid == 0)
	{
		return find_max(arr,N);
	}
	else
	{
		int retval = 0;
		int max = 0;
		wait(&retval);
		max = WEXITSTATUS(retval);

		printf("In parent-process,the max number is %d at %d\n",arr[max],max);
	}
	return 0;
}

int input_arr(int *parr,int cnt)
{
	int *pi = NULL;

	printf("Please input %d numbers:\n",cnt);
	for(pi=parr;pi < parr + cnt;pi++)
	{
		scanf("%d",pi);
	}

	return 0;
}

int find_max(int *parr,int cnt)
{
	int max = 0;
	int i = 0;

	for(i = 1;i < cnt;i++)
	{
		if(*(parr+i) > *(parr+max))
		{
			max = i;
		}
	}

	return max;
}

