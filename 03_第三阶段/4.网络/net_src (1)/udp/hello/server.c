#include <arpa/inet.h>
#include <unistd.h>

#include <stdio.h>
#include <string.h>

int main(int argc,char *argv[])
{
	int sockfd = -1;
	struct sockaddr_in servaddr;
	struct sockaddr_in cliaddr;
	socklen_t socklen = 0;
	char buf[8] = "";
	int ret = 0;

	sockfd = socket(AF_INET,SOCK_DGRAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(7878);
	inet_aton("127.0.0.1",&servaddr.sin_addr);

	ret = bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(ret < 0)
	{
		close(sockfd);
		sockfd = -1;
		printf("server error:bind failed\n");
		return 1;
	}

	while(1)
	{
		socklen = sizeof(cliaddr);
		ret = recvfrom(sockfd,buf,8,0,(struct sockaddr *)&cliaddr,&socklen);
		if(ret < 0)
		{
			break;
		}
		printf("In server,buf=%s\n",buf);

		ret = sendto(sockfd,"hello",6,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
		if(ret != 6)
		{
			break;
		}
	}

	close(sockfd);
	sockfd = -1;
	return 0;
}
