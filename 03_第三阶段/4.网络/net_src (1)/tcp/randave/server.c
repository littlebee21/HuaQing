#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int create_server_socket(char *ip,unsigned short port);
int server_main_loop(int servfd);
int main(int argc,char *argv[])
{
	int connectfd = -1;
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

	connectfd = create_server_socket(argv[1],(unsigned short)intport);
	if(connectfd < 0)
	{
		printf("create_server_socket failed\n");
		return 3;
	}

	server_main_loop(connectfd);

	close(connectfd);
	connectfd = -1;

	return 0;
}

int handle_client(int datafd);
int server_main_loop(int servfd)
{
	int datafd = -1;
	int ret = 0;
	while(1)
	{
		datafd = accept(servfd,NULL,NULL);
		if(datafd == -1)
		{
			if(errno == EINTR)
			{
				continue;
			}
			else
			{
				printf("accpet error\n");
				ret = -1;
				break;
			}
		}
		handle_client(datafd);
	}//end while(1)
	return ret;
}

int print_rands(int *prand,int num)
{
	int i = 0;

	for(i = 0;i < num;i++)
	{
		printf("%d ",*(prand+i));
	}
	printf("\n");

	return 0;
}

float get_rands_ave(int *prand,int num)
{
	float sum = 0.0;
	int i = 0;

	for(i = 0;i < num;i++)
	{
		sum += *(prand + i);
	}

	return sum/num;
}

int handle_client(int datafd)
{
	int ret = 0;
	int cnt = 0;
	int *pi = 0;
	float ave = 0.0f;

	while(1)
	{
		/*recv cnt from client*/
		ret = recv(datafd,&cnt,sizeof(int),0);
		if(ret <= 0)
		{
			printf("client is close or recv error\n");
			break;
		}

		/*malloc for rands*/
		pi = (int *)malloc(cnt * sizeof(int));
		if(NULL == pi)
		{
			printf("malloc for rands failed\n");
			break;
		}
		memset(pi,0,cnt * sizeof(int));

		/*recv cnt-rands*/
		ret = recv(datafd,pi,cnt * sizeof(int),0);
		if(ret <= 0)
		{
			printf("client is close or recv error\n");
			break;
		}
		
		/*print recv data*/
		print_rands(pi,cnt);

		/*calc ave*/
		ave = get_rands_ave(pi,cnt);

		/*free pi-mem*/
		free(pi);
		pi = NULL;
	
		/*send ave to client*/
		ret = send(datafd,&ave,sizeof(float),0);
		if(ret != sizeof(float))
		{
			printf("send ave to client failed\n");
			break;
		}

	}
	close(datafd);
	datafd = -1;

	return 0;
}

int create_server_socket(char *ip,unsigned short port)
{
	int servfd = -1;
	struct sockaddr_in servaddr;
	int ret = 0;
	
	servfd = socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	inet_aton(ip,&servaddr.sin_addr);

	ret = bind(servfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	ret += listen(servfd,6);
	if(ret)
	{
		printf("bind or listen failed\n");
		close(servfd);
		servfd = -1;
	}
	return servfd;
}
