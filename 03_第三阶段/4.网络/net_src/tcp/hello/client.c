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


	/*内核创建一个使用TCP方式传输应用层数据的操作引擎，并将该引擎的内存地址填入当前进程的描述符数组，返回对应的下标
	 *
	 *此时创建出来的套接字（socket）被称为主动套接字，理解上可以想象成----插头
	 * */
	sockfd = socket(AF_INET,SOCK_STREAM,0);


	/*填写服务端的IP地址和端口号
	 * 注意后续函数中要求的都是网络字节序的IP地址和端口号
	 * */
	bzero(&servaddr,sizeof(servaddr));//将servaddr变量空间的所有字节设置为0
	servaddr.sin_family = AF_INET;//说明本socket地址结构针对的是因特网这种互联网
	servaddr.sin_port = htons(3456);//服务端的端口号需要转成网络字节序
	inet_aton("127.0.0.1",&servaddr.sin_addr);//inet_aton转换得到四字节整型IP地址已是网络字节序
	/*127.0.0.1 本地环回IP地址，本地环回是一种虚拟网卡，向该网卡发送的数据不会发送出去，只会环回给本电脑
	 *为了程序员开发调试方便，基本上所有操作系统都会实现一个本地环回的虚拟网卡
	 * */


	/*
	 * 通过三路握手的方式与指定服务器进程建立好逻辑上的连接
	 * connect能正常返回的基本前提：
	 * 1. 客户端电脑与服务器电脑网络联通正常
	 * 2. 服务端程序已经运行（listen函数执行完）
	 * */
	ret = connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(ret < 0)
	{
		close(sockfd);
		sockfd = -1;
		printf("connect server failed\n");
		return 1;
	}

	/*开始与服务器进行数据交互，交互次数以及每次交互的数据格式由应用层协议指定*/
	write(sockfd,"hello",6);

	read(sockfd,buf,8);
	printf("Server say to me:%s\n",buf);

	close(sockfd);//通过四路握手的方式与服务器断开连接，此后无法再用该描述符与服务端继续数据交互
	sockfd = -1;
	return 0;
}
