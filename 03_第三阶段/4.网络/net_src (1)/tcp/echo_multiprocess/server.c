#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

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
	pid_t pid;

	signal(SIGCHLD,SIG_IGN);
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

		pid = fork();
		if(pid < 0)
		{
			close(datafd);
			datafd = -1;
			continue;
		}
		if(pid == 0)
		{
			close(servfd);
			servfd = -1;
			handle_client(datafd);
			exit(0);
		}
		else
		{
			close(datafd);
			datafd = -1;
		}
	}//end while(1)
	return ret;
}

int handle_client(int datafd)
{
	int ret = 0;
	char buf[40] = "";

	while(1)
	{
		/*recv data from client*/
		ret = recv(datafd,buf,40,0);
		if(ret <= 0)
		{
			printf("client is close or recv error\n");
			break;
		}

		/*print recv data*/
		printf("Client say to me:%s\n",buf);

		ret = send(datafd,buf,strlen(buf),0);
		if(ret != strlen(buf))
		{
			printf("send string to client failed\n");
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
