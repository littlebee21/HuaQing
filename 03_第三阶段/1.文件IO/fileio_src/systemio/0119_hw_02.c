/*程序产生n个随机数，n由用户输入，先将n个随机数保存到文件in.dat中，
      然后从in.dat的start位置开始中读出m个随机数，start和m也由用户输入，
      在标准输出中先打印m个随机数，然后求其均值输出，再排序后保存到out.dat中
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int input_number(char *ptip);
int *create_n_rands(int n);
int write_nrand_to_file(int *pi,int cnt,int fd);
int read_nrand_from_file(int *pi,int cnt,int start,int fd);
float get_ave(int *pi,int cnt);
int intcmp(const void *pv1,const void *pv2);

#define IN_FILE "./in.dat"
#define OUT_FILE "./out.dat"
int main(int argc,char *argv[])
{
	int cnt = input_number("Please input a number:\n");
	int *pi = NULL;
	int infd = -1;
	int outfd = -1;
	int start = 0;
	int m = 0;
	int *prd = NULL;
	
	srand(time(NULL));
	
	pi = create_n_rands(cnt);

	infd = open(IN_FILE,O_RDWR | O_CREAT | O_TRUNC,0666);
	if(infd < 0)
	{
		printf("rdwr-open %s failed\n",IN_FILE);
		return 1;
	}

	write_nrand_to_file(pi,cnt,infd);
	free(pi);
	pi = NULL;

	start = input_number("Please input a start location:\n");
	m = input_number("Please input a count:\n");

	prd = (int *)malloc(m * sizeof(int));
	if(NULL == prd)
	{
		printf("Malloc for %d int-element failed\n",m);
		return 2;
	}
	memset(prd,0,m * sizeof(int));

	m = read_nrand_from_file(prd,m,start,infd);
	close(infd);
	infd = -1;

	printf("The ave of m-rands is %.2f\n",get_ave(prd,m));

	qsort(prd,m,sizeof(int),intcmp);

	outfd = open(OUT_FILE,O_WRONLY | O_CREAT | O_TRUNC,0666);
	if(outfd < 0)	
	{
		printf("wronly-open %s failed\n",OUT_FILE);
		return 3;
	}

	write_nrand_to_file(prd,m,outfd);

	free(prd);
	prd = NULL;
	close(outfd);
	outfd = -1;
	return 0;
}

int intcmp(const void *pv1,const void *pv2)
{
	return *(int *)pv1 - *(int *)pv2;
}

float get_ave(int *pi,int cnt)
{
	float sum = 0.0f;
	int i = 0;

	for(i = 0;i < cnt;i++)
	{
		sum += *(pi + i);
	}

	return sum / cnt;
}

int write_nrand_to_file(int *pi,int cnt,int fd)
{
	int ret = 0;

	ret = write(fd,pi,cnt * sizeof(int));
	if(ret != cnt * sizeof(int))
	{
		printf("write %d rands to file failed\n",cnt);
		return -1;
	}

	return 0;
}

int read_nrand_from_file(int *pi,int cnt,int start,int fd)
{
	int ret = 0;

	ret = lseek(fd,start * sizeof(int),SEEK_SET);
	if(ret < 0)
	{
		printf("start is too big\n");
		return -1;
	}

	ret = read(fd,pi,cnt * sizeof(int));
	if(ret < 0)
	{
		printf("read rand from file failed\n");
		return -1;
	}

	return ret/sizeof(int);
}

int *create_n_rands(int n)
{
	int *pi = NULL;
	int i = 0;

	pi = (int *)malloc(n * sizeof(int));
	if(NULL == pi)
	{
		printf("Malloc failed for %d int-element\n",n);
		return NULL;
	}
	memset(pi,0,n * sizeof(int));

	for(i = 0;i < n;i++)
	{
		*(pi + i) = rand() % 10000;
	}

	return pi;
}

int input_number(char *ptip)
{
	int v = 0;

	printf("%s",ptip);
	scanf("%d",&v);

	while(getchar() != '\n')
	{
	}
	return v; 
}
