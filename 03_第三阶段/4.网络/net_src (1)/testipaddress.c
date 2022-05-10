#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>

int main(int argc,char *argv[])
{
	struct in_addr ipaddr;
	int ret = 0;

	if(argc < 2)
	{
		printf("The argument is too few\n");
		return 1;
	}

	ret = inet_aton(argv[1],&ipaddr);
	if(!ret)
	{
		printf("inet_aton failed\n");
		return 2;
	}

	printf("The ip is %s\n",inet_ntoa(ipaddr));

	return 0;
}
