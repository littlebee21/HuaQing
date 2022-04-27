#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <errno.h>

#include <stdio.h>
#include <string.h>

int main(int argc,char *argv[])
{
	int servfd = -1;
	struct sockaddr_in servaddr;
	int ret = 0;
	int datafd = -1;
	char buf[8] = "";

	struct sockaddr_in cliaddr;
	socklen_t socklen; 

	/*内核创建一个使用TCP方式传输应用层数据的操作引擎，并将该引擎的内存地址填入当前进程的描述符数组，返回对应的下标
	 *
	 *此时创建出来的套接字（socket）被称为主动套接字，理解上可以想象成----插头
	 * */
	servfd = socket(AF_INET,SOCK_STREAM,0);

	/*填写服务端自身的IP地址和端口号
	 * 注意后续函数中要求的都是网络字节序的IP地址和端口号
	 * */
	bzero(&servaddr,sizeof(servaddr));//将servaddr变量空间的所有字节设置为0
	servaddr.sin_family = AF_INET;//说明本socket地址结构针对的是因特网这种互联网
	servaddr.sin_port = htons(3456);////服务端的端口号需要转成网络字节序
	inet_aton("127.0.0.1",&servaddr.sin_addr);//inet_aton转换得到四字节整型IP地址已是网络字节序

	/*为前面socket函数创建的操作引擎指定服务端自身的IP地址和端口号*/
	ret = bind(servfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	ret += listen(servfd,6);//将主动套接字变换为被动套接字，此后专门用该套接字对应的引擎处理客户端的连接请求,理解上可以将被动套接字想象成专门提供插孔的玄幻插排（玄幻是指可以智能提供插孔）
	if(ret < 0)
	{
		close(servfd);
		servfd = -1;
		perror("bind or listen failed:");
		return 1;
	}

	while(1)
	{
		socklen = sizeof(cliaddr);

		/*检查是否有客户端与服务器通过三路握手建立好连接，如果没有则阻塞，一旦发现有就会创建一个新的操作引擎，
		 * 此后用该引擎与对应的客户端进行数据交互，并将该引擎的内存地址填入服务器进程的描述符数组中，返回对应
		 * 的下标----即数据交互用描述符，理解上可以想象成插排上的一个插孔
		 * 
		 * int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
		 * addr参数：结果参数
		 * addrlen参数：值-结果参数
		 * 如果不关心已连接客户端的IP地址和端口号，则可以这个参数可以填NULL
		 * */
		datafd = accept(servfd,(struct sockaddr *)&cliaddr,&socklen);
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

		printf("client ipaddr = %s\n",inet_ntoa(cliaddr.sin_addr));
		printf("client port = %d\n",ntohs(cliaddr.sin_port));


		/*开始与对应客户端进行数据交互，交互次数和每次交互的数据格式，由应用层协议指定
		 * 应用层协议则根据要完成的网络功能来制定*/
		read(datafd,buf,8);
		printf("client say to me:%s\n",buf);
		
		write(datafd,buf,6);

		close(datafd);//四路握手断开与对应客户端的连接，此后无法再用该描述符与对应客户端进行数据交互
		datafd = -1;
	}


	close(servfd);//关闭专门处理客户端连接请求用的描述符
	servfd = -1;
	return 0;
}
