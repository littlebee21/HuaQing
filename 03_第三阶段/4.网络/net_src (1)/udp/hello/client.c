#include <arpa/inet.h>
#include <unistd.h>

#include <stdio.h>
#include <string.h>

int main(int argc,char *argv[])
{
	int sockfd = -1;
	struct sockaddr_in servaddr;
	char buf[8] = "";

	sockfd = socket(AF_INET,SOCK_DGRAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(7878);
	inet_aton("127.0.0.1",&servaddr.sin_addr);


	sendto(sockfd,"hello",6,0,(struct sockaddr *)&servaddr,sizeof(servaddr));

	recvfrom(sockfd,buf,8,0,NULL,NULL);
	printf("In client,buf=%s\n",buf);

	close(sockfd);
	sockfd = -1;
	return 0;
}
