#include <arpa/inet.h>
#include <unistd.h>

#include <stdio.h>
#include <string.h>
char *mygetstring(char *buf,int size);
int main(int argc,char *argv[])
{
	int sockfd = -1;
	struct sockaddr_in servaddr;
	char sndbuf[40] = "";
	char rcvbuf[40] = "";

	sockfd = socket(AF_INET,SOCK_DGRAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(7878);
	inet_aton("127.0.0.1",&servaddr.sin_addr);

	while(1)
	{
		printf("Please input a string,input quit will exit this program:\n");
		mygetstring(sndbuf,40);

		if(strcmp(sndbuf,"") == 0)
		{
			continue;
		}
		if(strcmp(sndbuf,"quit") == 0)
		{
			break;
		}

		sendto(sockfd,sndbuf,strlen(sndbuf)+1,0,(struct sockaddr *)&servaddr,sizeof(servaddr));

		recvfrom(sockfd,rcvbuf,40,0,NULL,NULL);
		printf("In client,buf=%s\n",rcvbuf);
	}
	close(sockfd);
	sockfd = -1;
	return 0;
}
