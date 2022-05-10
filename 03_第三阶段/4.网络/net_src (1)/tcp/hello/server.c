#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#include <stdio.h>
#include <string.h>

int main(int argc,char *argv[])
{
	int servfd = -1;
	int datafd = -1;
	struct sockaddr_in servaddr;
	int ret = 0;
	char buf[8] = "";

	struct sockaddr_in cliaddr;
	socklen_t addrlen = 0;

	servfd = socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(6789);
	inet_aton("127.0.0.1",&servaddr.sin_addr);

	ret = bind(servfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	ret += listen(servfd,6);
	if(ret)
	{
		printf("bind or listen failed\n");
		close(servfd);
		servfd = -1;
		return 1;
	}

	while(1)
	{
		addrlen = sizeof(cliaddr);
		datafd = accept(servfd,(struct sockaddr *)&cliaddr,&addrlen);
		if(datafd == -1)
		{
			if(errno == EINTR)
			{
				continue;
			}
			else
			{
				printf("accpet error\n");
				break;
			}
		}
		printf("client ip = %s\n",inet_ntoa(cliaddr.sin_addr));

		read(datafd,buf,8);
		printf("Server recv data:%s\n",buf);
			
		write(datafd,"hello",sizeof("hello"));
		close(datafd);
		datafd = -1;
	}//end while(1)

	close(servfd);
	servfd = -1;

	return 0;
}


