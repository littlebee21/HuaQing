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

	sockfd = socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));//memset(&servaddr,0,sizeof(servaddr)); 将servaddr变量空间清零
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(6789);
	inet_aton("127.0.0.1",&servaddr.sin_addr);

	ret = connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(ret)
	{
		printf("connect server failed\n");
		close(sockfd);
		sockfd = -1;
		return 1;
	}

	write(sockfd,"hello",sizeof("hello"));

	read(sockfd,buf,8);
	printf("Client recv data:%s\n",buf);

	close(sockfd);
	sockfd = -1;
	return 0;
}
