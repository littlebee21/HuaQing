#include <arpa/inet.h>
#include <unistd.h>

#include <stdio.h>
#include <string.h>

int create_client_socket(char *ip,unsigned short port);
char *mygetstring(char *buf,int size);
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


	client_main_loop(fd);


	close(fd);
	fd = -1;
	return 0;
}

int client_main_loop(int fd)
{
	char sndbuf[40] = "";
	char rcvbuf[40] = "";
	int ret = 0;

	while(1)
	{
		/*recv user input*/
		printf("Please input a string:\n");
		mygetstring(sndbuf,40);

		/*is quit*/
		if(strcmp(sndbuf,"quit") == 0)
		{
			ret = 0;
			break;
		}
		
		/*send buf to server*/
		ret=send(fd,sndbuf,strlen(sndbuf),0);
		if(ret != strlen(sndbuf))
		{
			printf("send %s to server failed\n",sndbuf);
			ret = -1;
			break;
		}

		/*recv data from server*/
		ret = recv(fd,rcvbuf,40,0);
		if(ret <= 0)
		{
			printf("recv string frem server failed\n");
			ret = -1;
			break;
		}

		/*print recv data*/
		printf("Server say to me:%s\n",rcvbuf);
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

