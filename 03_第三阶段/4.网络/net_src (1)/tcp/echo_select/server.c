#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#include <stdio.h>
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
	fd_set rfds;
	fd_set rfdsbak;
	int i = 0;

	FD_ZERO(&rfdsbak);
	FD_SET(servfd,&rfdsbak);

	while(1)
	{
		memcpy(&rfds,&rfdsbak,sizeof(fd_set));
		ret = select(FD_SETSIZE,&rfds,NULL,NULL,NULL);
		if(ret < 0)
		{
			if(errno == EINTR)
			{
				continue;
			}
			else
			{
				break;
			}
		}

		for(i = 0;i < FD_SETSIZE;i++)
		{
			if(i == servfd)
			{
				if(FD_ISSET(servfd,&rfds))
				{
					datafd = accept(servfd,NULL,NULL);
					FD_SET(datafd,&rfdsbak);
				}
			}
			else
			{
				if(FD_ISSET(i,&rfds))
				{
					if(handle_client(i) < 0)
					{
						FD_CLR(i,&rfdsbak);
					}
				}

			}
		}

	}//end while(1)
	return ret;
}

int handle_client(int datafd)
{
	int ret = 0;
	char buf[40] = "";

	do
	{
		/*recv data from client*/
		ret = recv(datafd,buf,40,0);
		if(ret <= 0)
		{
			printf("client is close or recv error\n");
			ret = -1;
			break;
		}

		/*print recv data*/
		printf("Client say to me:%s\n",buf);

		ret = send(datafd,buf,strlen(buf),0);
		if(ret != strlen(buf))
		{
			printf("send string to client failed\n");
			ret = -1;
			break;
		}
		ret = 0;
	}while(0);

	if(ret < 0)
	{
		close(datafd);
		datafd = -1;
	}

	return ret;
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
