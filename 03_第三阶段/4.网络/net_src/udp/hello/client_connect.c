#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <stdio.h>
#include <string.h>

int main(int argc,char *argv[])
{
	int sockfd = -1;
	struct sockaddr_in servaddr;
	int ret = 0;
	char buf[8] = "";

	sockfd = socket(AF_INET,SOCK_DGRAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9988);
	inet_aton("127.0.0.1",&servaddr.sin_addr);

	/*与TCP客户端调用connect函数不一样，没有所谓的三路握手过程，作用也不是所谓的建立连接
	 *UDP客户端调用本函数的作用：
	 1. 先做网络连通性的检查
	 2. 将本udp-socket做成定向传输（只与指定IP地址的主机和指定端口号的进程进行数据交互）
	 * */
	ret = connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(ret < 0)
	{
		printf("udp client connect failed\n");
		return 4;
	}


	//ret = sendto(sockfd,"hello",6,0,NULL,0);
	//ret = send(sockfd,"hello",6,0);
	ret = write(sockfd,"hello",6);
	if(ret != 6)
	{
		printf("sendto failed\n");
		close(sockfd);
		sockfd = -1;
		return 1;
	}

	//ret = recvfrom(sockfd,buf,8,0,NULL,NULL);
	ret = recv(sockfd,buf,8,0);
	//ret = read(sockfd,buf,8);
	if(ret < 0)
	{
		printf("recvfrom failed\n");
		close(sockfd);
		sockfd = -1;
		return 2;
	}

	printf("Server Say to me:%s\n",buf);

	close(sockfd);
	sockfd = -1;
	return 0;
}
