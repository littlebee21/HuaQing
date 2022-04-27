#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#include <stdio.h>
#include <string.h>

int main(int argc,char *argv[])
{
	int sockfd = -1;
	int datafd = -1;
	struct sockaddr_un servaddr;
	int ret = 0;
	char buf[8] = "";

	sockfd = socket(AF_UNIX,SOCK_STREAM,0);	

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sun_family = AF_UNIX;
	strcpy(servaddr.sun_path,"/tmp/myxyz");

	ret = bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	ret += listen(sockfd,6);
	if(ret < 0)
	{
		close(sockfd);
		sockfd = -1;
		perror("bind or listen failed:");
		return 1;
	}

	while(1)
	{
		datafd = accept(sockfd,NULL,NULL);
		if(datafd < 0)
		{
			if(errno == EINTR)
			{
				continue;
			}
			else
			{
				perror("accept failed:");
				break;
			}
		}

		read(datafd,buf,8);

		printf("Client say to me:%s\n",buf);

		write(datafd,buf,strlen(buf) + 1);

		close(datafd);
		datafd = -1;
	}


	close(sockfd);
	sockfd = -1;

	return 0;
}
