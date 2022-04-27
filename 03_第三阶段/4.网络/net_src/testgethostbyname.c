#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>

int main(int argc,char *argv[])
{
	struct hostent *pret = NULL;

	if(argc < 2)
	{
		printf("The argument is too few\n");
		return 1;
	}

	pret = gethostbyname(argv[1]);
	if(NULL == pret)
	{
		/*失败原因：
		 * 1. 运行本程序的电脑未联网
		 * 2. 系统中DNS服务器IP地址的设置有问题
		 * 3. 提供DNS服务的主机宕机
		 * */
		printf("gethostbyname failed\n");
		return 2;
	}

	printf("The offical name is %s\n",pret->h_name);


	{
		char **ppalias = NULL;

		ppalias = pret->h_aliases;
		while(*ppalias != NULL)
		{
			printf("The aliases name is %s\n",*ppalias);

			ppalias++;
		}
	}


	{
		struct in_addr **ppip = NULL;
		
		ppip = (struct in_addr **)pret->h_addr_list;
		while(*ppip != NULL)
		{
			printf("IP Address is %s\n",inet_ntoa(**ppip));
			ppip++;
		}
	}

	/*项目中如果知道服务端域名，而服务端有多个IP地址，一般我们直接使用其第一个IP地址即可*/
	/*
	 * struct hostent *pret = NULL;
	 * pret = gethostbyname("域名");
	 *servaddr.sin_addr = **(struct in_addr **)pret->h_addr_list;
	 * */

	return 0;
}
