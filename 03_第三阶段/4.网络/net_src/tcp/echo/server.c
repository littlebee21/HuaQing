#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <errno.h>

#include <stdio.h>
#include <string.h>

int create_tcp_server_socket(char *ipaddr,unsigned short port);
int server_main_loop(int servfd);
int main(int argc,char *argv[])
{
	int servfd = -1;
	int iport = -1;

	if(argc < 3)
	{
		printf("The argument is too few\n");
		return 1;
	}

	sscanf(argv[2],"%d",&iport);
	if(iport < 0 || iport > 0xFFFF)
	{
		printf("The port is invalid\n");
		return 2;
	}

	servfd = create_tcp_server_socket(argv[1],(unsigned short)iport);
	if(servfd < 0)
	{
		printf("create_tcp_server_socket failed\n");
		return 3;
	}

	server_main_loop(servfd);

	close(servfd);
	servfd = -1;
	return 0;
}

int handle_client_data(int datafd);
int server_main_loop(int servfd)
{
	int datafd = -1;

	while(1)
	{
		datafd = accept(servfd,NULL,NULL);
		if(datafd < 0)
		{
			if(errno == EINTR)
			{//本次错误是信号引起，可会忽略本错误
				continue;
			}
			else
			{
				perror("accept failed:");
				break;
			}
		}
		handle_client_data(datafd);
	}

	return 0;
}

int handle_client_data(int datafd)
{
	char buf[160] = "";
	int ret = 0;
	int sendlen = 0;

	while(1)
	{
		/*读客户发过来的字符串 read或recv返回值 <= 0 break*/
		ret = read(datafd,buf,160);
		if(ret <= 0)
		{
			printf("recv client data failed or client close link\n");
			break;
		}

		printf("Client say to me:%s\n",buf);

		/*将收到的字符串发回给客户端*/
		sendlen = strlen(buf) + 1;
		ret = write(datafd,buf,sendlen);
		if(ret != sendlen)
		{
			printf("send data to client failed\n");
			break;
		}
	}

	close(datafd);
	datafd = -1;

	return 0;
}

int create_tcp_server_socket(char *ipaddr,unsigned short port)
{
	int servfd = -1;
	struct sockaddr_in servaddr;
	int ret = 0;

	servfd = socket(AF_INET,SOCK_STREAM,0);
	if(servfd < 0)
	{
		printf("call socket function failed\n");
		return -1;
	}

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	inet_aton(ipaddr,&servaddr.sin_addr);

	ret = bind(servfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	ret += listen(servfd,6);
	if(ret < 0)
	{
		close(servfd);
		servfd = -1;
		perror("bind or listen failed:");
		return -1;
	}

	return servfd;
}
