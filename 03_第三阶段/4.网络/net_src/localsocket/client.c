#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/un.h>

#include <stdio.h>
#include <string.h>

int main(int argc,char *argv[])
{
	int sockfd = -1;
	struct sockaddr_un servaddr;
	int ret = 0;
	char buf[8] = "";

	sockfd = socket(AF_UNIX,SOCK_STREAM,0);	

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sun_family = AF_UNIX;
	strcpy(servaddr.sun_path,"/tmp/myxyz");

	ret = connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(ret < 0)
	{
		close(sockfd);
		sockfd = -1;
		perror("connect server failed:");
		return 1;
	}


	write(sockfd,"hello",6);

	read(sockfd,buf,8);

	printf("Server say to me:%s\n",buf);

	close(sockfd);
	sockfd = -1;

	return 0;
}
