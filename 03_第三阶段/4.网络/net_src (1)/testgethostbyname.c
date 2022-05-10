#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>

int main(int argc,char *argv[])
{
	struct hostent *pret = NULL;
	char **ppalias = NULL;
	struct in_addr **ppaddr = NULL;

	if(argc < 0)
	{
		printf("The argument is too few\n");
		return 1;
	}

	pret = gethostbyname(argv[1]);
	if(NULL == pret)
	{
		printf("gethostbyname failed\n");
		return 2;
	}

	printf("The offical-name is %s\n",pret->h_name);
	ppalias = pret->h_aliases;
	while(*ppalias != NULL)
	{
		printf("alias-name is %s\n",*ppalias);
		ppalias++;
	}

	ppaddr = (struct in_addr **)pret->h_addr_list;
	while(*ppaddr != NULL)
	{
		printf("IP-Addr is %s\n",inet_ntoa(**ppaddr));
	
		ppaddr++;
	}


	return 0;
}
