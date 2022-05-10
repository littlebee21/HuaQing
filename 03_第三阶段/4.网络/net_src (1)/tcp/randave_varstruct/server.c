#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#include "protocol.h"

int create_server_socket(char *ip,unsigned short port);
int server_main_loop(int servfd);
int main(int argc,char *argv[])
{
	int connectfd = -1;
	int intport = -1;

	if(argc < 3)
	{
		printf("The argument is too few\n");
		return 1;
	}

	sscanf(argv[2],"%d",&intport);
	if(intport < 0 || intport > 0xffff)
	{
		printf("port is invalid\n");
		return 2;
	}

	connectfd = create_server_socket(argv[1],(unsigned short)intport);
	if(connectfd < 0)
	{
		printf("create_server_socket failed\n");
		return 3;
	}

	server_main_loop(connectfd);

	close(connectfd);
	connectfd = -1;

	return 0;
}

int handle_client(int datafd);
int server_main_loop(int servfd)
{
	int datafd = -1;
	int ret = 0;
	while(1)
	{
		datafd = accept(servfd,NULL,NULL);
		if(datafd == -1)
		{
			if(errno == EINTR)
			{
				continue;
			}
			else
			{
				printf("accpet error\n");
				ret = -1;
				break;
			}
		}

		handle_client(datafd);
	}//end while(1)
	return ret;
}

int print_rands(int *prand,int num)
{
	int i = 0;

	for(i = 0;i < num;i++)
	{
		printf("%d ",*(prand+i));
	}
	printf("\n");

	return 0;
}

int handle_client(int datafd)
{
	int ret = 0;
	struct rands_pdu *precv = NULL;
	struct rands_pdu *psend = NULL;

	while(1)
	{
		/*recv rands pdu*/
		precv = recv_rands_pdu(datafd);
		if(precv == NULL)
		{
			break;
		}
		/*print recv data*/
		print_rands((int *)precv->buf,precv->len / sizeof(int));

		switch(precv->type)
		{
			case PDU_TYPE_AVE_REQ:
				psend = create_ave_rsp_pdu((int *)precv->buf,precv->len / sizeof(int));
				break;
			case PDU_TYPE_MAX_REQ:
				psend = create_max_rsp_pdu((int *)precv->buf,precv->len / sizeof(int));
				break;
			case PDU_TYPE_MIN_REQ:
				psend = create_min_rsp_pdu((int *)precv->buf,precv->len / sizeof(int));
				break;
		}

		/*create ave pdu*/
		destroy_rands_pdu(precv);
		precv = NULL;
		if(psend == NULL)
		{
			break;
		}

		/*send ave to client*/
		ret = send_rands_pdu(datafd,psend);
		destroy_rands_pdu(psend);
		psend = NULL;
		if(ret)
		{
			break;
		}
	}
	close(datafd);
	datafd = -1;

	return 0;
}

int create_server_socket(char *ip,unsigned short port)
{
	int servfd = -1;
	struct sockaddr_in servaddr;
	int ret = 0;
	
	servfd = socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	inet_aton(ip,&servaddr.sin_addr);

	ret = bind(servfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	ret += listen(servfd,6);
	if(ret)
	{
		printf("bind or listen failed\n");
		close(servfd);
		servfd = -1;
	}
	return servfd;
}
