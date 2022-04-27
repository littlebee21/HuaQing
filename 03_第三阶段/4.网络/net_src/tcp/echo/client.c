#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <stdio.h>
#include <string.h>

int create_tcp_client_socket(char *ipaddr,unsigned short port);
int client_main_loop(int sockfd);

int main(int argc,char *argv[])
{
	int sockfd = -1;
	int iport = 0;

	if(argc < 3)
	{
		printf("The argument is too few\n");
		return 1;
	}

	sscanf(argv[2],"%d",&iport);
	if(iport < 0 || iport > 0xFFFF)
	{
		printf("port is invalid\n");
		return 2;
	}

	sockfd = create_tcp_client_socket(argv[1],(unsigned short)iport);
	if(sockfd < 0)
	{
		printf("create_tcp_client_socket failed\n");
		return 3;
	}

	client_main_loop(sockfd);


	close(sockfd);
	sockfd = -1;
	return 0;
}

char *mygets(char *pout,int size);
int client_main_loop(int sockfd)
{
	char buf[160] = "";
	int ret = 0;
	int sendlen = 0;

	while(1)
	{
		/*用户输入字符串 ---- 限定与服务器交互的字符串长度最大为159*/
		printf("Please input a string:\n");
		mygets(buf,160);

		/*检查用户输入的字符串内容是不是"quit",如果是则break*/
		if(strcmp(buf,"quit") == 0)
		{
			break;
		}

		/*发送用户输入的字符串*/
		sendlen = strlen(buf) + 1;
		ret = write(sockfd,buf,sendlen);
		if(ret != sendlen)
		{
			printf("send %s failed\n",buf);
			break;
		}

		/*接收服务器发回的字符串----如果接收到字节数<0说明出错，==0说明服务器已经断开了与本客户端的连接*/
		memset(buf,0,160);
		ret = read(sockfd,buf,160);
		if(ret <= 0)
		{
			printf("recv data error or server close link\n");
			break;
		}

		/*打印收到的字符串*/
		printf("Server Say to me:%s\n",buf);
	}

	return 0;
}

int create_tcp_client_socket(char *ipaddr,unsigned short port)
{
	int sockfd = -1;
	int ret = 0;
	struct sockaddr_in servaddr;

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0)
	{
		printf("call socket function failed\n");
		return -1;
	}

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	inet_aton(ipaddr,&servaddr.sin_addr);
	
	ret = connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(ret < 0)
	{
		close(sockfd);
		sockfd = -1;
		printf("connect server failed\n");
		return ret;
	}

	return sockfd;
}
