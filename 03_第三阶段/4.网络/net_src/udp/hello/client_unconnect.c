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

	ret = sendto(sockfd,"hello",6,0,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(ret != 6)
	{
		printf("sendto failed\n");
		close(sockfd);
		sockfd = -1;
		return 1;
	}

	ret = recvfrom(sockfd,buf,8,0,NULL,NULL);
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
