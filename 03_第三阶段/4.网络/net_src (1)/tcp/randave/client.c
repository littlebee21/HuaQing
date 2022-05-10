#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int create_client_socket(char *ip,unsigned short port);
int client_main_loop(int fd);
int main(int argc,char *argv[])
{
	int fd = -1;
	int intport = -1;

	if(argc < 3)
	{
		printf("The argument is too few\n");
		return 1;
	}

	sscanf(argv[2],"%d",&intport);
	if(intport < 0 || intport > 0xffff)
	{
		printf("port is invalid\n");
		return 2;
	}


	fd = create_client_socket(argv[1],(unsigned short)intport);
	if(fd < 0)
	{
		printf("create_client_socket failed\n");
		return 3;
	}

	srand(time(NULL));

	client_main_loop(fd);


	close(fd);
	fd = -1;
	return 0;
}

int client_main_loop(int fd)
{
	int ret = 0;
	int cnt = 0;
	int *pi = NULL;
	float ave = 0.0f;
	int i = 0;

	while(1)
	{
		/*recv user input*/
		printf("Please input a number:\n");
		scanf("%d",&cnt);

		/*is quit*/
		if(cnt <= 0)
		{
			ret = 0;
			break;
		}

		/*create cnt rands*/
		pi = (int *)malloc(cnt * sizeof(int));
		if(NULL == pi)
		{
			printf("malloc for cnt-rands failed\n");
			ret = -1;
			break;
		}
		memset(pi,0,cnt * sizeof(int));

		for(i = 0;i < cnt;i++)
		{
			*(pi + i) = rand() % 1000;
		}
		
		/*send cnt to server*/
		ret=send(fd,&cnt,sizeof(int),0);
		if(ret != sizeof(int))
		{
			printf("send cnt to server failed\n");
			ret = -1;
			break;
		}


		/*send rands to server*/
		ret=send(fd,pi,cnt * sizeof(int),0);
		free(pi);
		pi = NULL;
		if(ret != cnt * sizeof(int))
		{
			printf("send %d-rands to server failed\n",cnt);
			ret = -1;
			break;
		}

		/*recv data from server*/
		ret = recv(fd,&ave,sizeof(float),0);
		if(ret <= 0)
		{
			printf("recv string frem server failed\n");
			ret = -1;
			break;
		}

		/*print recv data*/
		printf("The ave is:%.2f\n",ave);
	}
	return ret;
}

int create_client_socket(char *ip,unsigned short port)
{
	int sockfd = -1;
	struct sockaddr_in servaddr;
	int ret = 0;

	sockfd = socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));//memset(&servaddr,0,sizeof(servaddr)); 将servaddr变量空间清零
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	inet_aton(ip,&servaddr.sin_addr);

	ret = connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(ret)
	{
		printf("connect server failed\n");
		close(sockfd);
		sockfd = -1;
	}

	return sockfd;
}

