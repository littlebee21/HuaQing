#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#include "protocol.h"

int create_client_socket(char *ip,unsigned short port);
int client_main_loop(int fd);
int main(int argc,char *argv[])
{
	int fd = -1;
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


	fd = create_client_socket(argv[1],(unsigned short)intport);
	if(fd < 0)
	{
		printf("create_client_socket failed\n");
		return 3;
	}

	srand(time(NULL));

	client_main_loop(fd);


	close(fd);
	fd = -1;
	return 0;
}

int display_operate_ui()
{
	int op = 0;

	printf("Please select your operate:\n");
	printf("1. Get Average\n");
	printf("2. Get Max Number\n");
	printf("3. Get Min Number\n");
	printf("0. Exit the program\n");
	scanf("%d",&op);

	return op;
}

int client_main_loop(int fd)
{
	int ret = 0;
	int cnt = 0;
	struct rands_pdu *psend = NULL;
	struct rands_pdu *precv = NULL;
	int op = 0;

	while(1)
	{
		/*recv user input*/
		printf("Please input a number,if less than zero will exit:\n");
		scanf("%d",&cnt);

		/*is quit*/
		if(cnt <= 0)
		{
			ret = 0;
			break;
		}

		op = display_operate_ui();
		switch(op)
		{
			case 1:
				psend = create_ave_req_pdu(cnt);
				break;
			case 2:
				psend = create_max_req_pdu(cnt);
				break;
			case 3:
				psend = create_min_req_pdu(cnt);
				break;
		}
		if(op <= 0 || op > 3) 
		{
			break;
		}
		/*create  rands pdu*/
		if(psend == NULL)
		{
			ret = -1;
			break;
		}
		
		/*send rands to server*/
		ret = send_rands_pdu(fd,psend);
		destroy_rands_pdu(psend);
		psend = NULL;
		if(ret)
		{
			break;
		}

		/*recv data from server*/
		precv = recv_rands_pdu(fd);
		if(precv == NULL)
		{
			ret = -1;
			break;
		}

		/*print recv data*/
		switch(precv->type)
		{
			case PDU_TYPE_AVE_RSP:
				printf("The ave is:%.2f\n",*(float *)precv->buf);
				break;
			case PDU_TYPE_MAX_RSP:
				printf("The max is:%d\n",*(int *)precv->buf);
				break;
			case PDU_TYPE_MIN_RSP:
				printf("The min is:%d\n",*(int *)precv->buf);
				break;
		}
		destroy_rands_pdu(precv);
		precv = NULL;
	}
	return ret;
}

int create_client_socket(char *ip,unsigned short port)
{
	int sockfd = -1;
	struct sockaddr_in servaddr;
	int ret = 0;

	sockfd = socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));//memset(&servaddr,0,sizeof(servaddr)); 将servaddr变量空间清零
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	inet_aton(ip,&servaddr.sin_addr);

	ret = connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(ret)
	{
		printf("connect server failed\n");
		close(sockfd);
		sockfd = -1;
	}

	return sockfd;
}

