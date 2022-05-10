#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#include <pthread.h>

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

void * handle_client(void *arg);
int server_main_loop(int servfd)
{
	int datafd = -1;
	int ret = 0;
	pthread_t tid;

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

		ret = pthread_create(&tid,NULL,handle_client,(void *)(long)datafd);
		if(ret)
		{
			close(datafd);
			datafd = -1;
			continue;
		}

	}//end while(1)
	return ret;
}

void * handle_client(void *arg)
{
	int ret = 0;
	char buf[40] = "";
	int datafd = (int)(long)arg;

	pthread_detach(pthread_self());
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

	return NULL;
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
