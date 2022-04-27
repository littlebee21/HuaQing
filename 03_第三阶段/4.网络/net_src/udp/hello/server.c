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
	struct sockaddr_in cliaddr;
	socklen_t addrlen;

	sockfd = socket(AF_INET,SOCK_DGRAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9988);
	inet_aton("127.0.0.1",&servaddr.sin_addr);

	ret = bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(ret < 0)
	{
		perror("bind failed:");
		return 1;
	}

	while(1)
	{

		addrlen = sizeof(cliaddr);
		ret = recvfrom(sockfd,buf,8,0,(struct sockaddr *)&cliaddr,&addrlen);
		if(ret < 0)
		{
			printf("recvfrom failed\n");
			close(sockfd);
			sockfd = -1;
			ret = 2;
			break;
		}

		printf("Server Say to me:%s\n",buf);

		ret = sendto(sockfd,buf,6,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
		if(ret != 6)
		{
			printf("sendto failed\n");
			close(sockfd);
			sockfd = -1;
			ret = 3;
			break;
		}
		else
		{
			ret = 0;
		}

	}

	close(sockfd);
	sockfd = -1;
	return ret;
}
