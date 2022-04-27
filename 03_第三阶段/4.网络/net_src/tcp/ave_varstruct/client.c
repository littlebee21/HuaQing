#include "avepdu.h"

int create_tcp_client_socket(char *ipaddr,unsigned short port);
int client_main_loop(int sockfd);

int main(int argc,char *argv[])
{
	int sockfd = -1;
	int iport = 0;

        if(argc < 3)
        {
                printf("The argument is too few\n");
                return 1;
        }

        sscanf(argv[2],"%d",&iport);
        if(iport < 0 || iport > 0xFFFF)
        {
                printf("port is invalid\n");
                return 2;
        }

        sockfd = create_tcp_client_socket(argv[1],(unsigned short)iport);
        if(sockfd < 0)
        {
                printf("create_tcp_client_socket failed\n");
                return 3;
	}

	srand(time(NULL));


	client_main_loop(sockfd);

	close(sockfd);
	sockfd = -1;

	return 0;
}

int input_count();
int client_main_loop(int sockfd)
{
	struct avepdu *pdu = NULL;
	struct avepdu *rsppdu = NULL;
	int n = 0;
	int ret = 0;
	while(1)
	{
		/*用户输入随机数个数n*/
		n = input_count();

		/*如果n <= 0则break*/
		if(n <= 0)
		{
			break;
		}

		/*创建pdu*/
		pdu = create_avepdu(n);
		if(NULL == pdu)
		{
			printf("call create_avepdu failed\n");
			break;
		}

		/*发送pdu*/
		ret = send_avepdu(sockfd,pdu);
		/*销毁pdu*/
		destroy_avepdu(pdu);
		pdu = NULL;
		if(ret != 0)
		{
			printf("call send_avepdu failed\n");
			break;
		}

		rsppdu = recv_avepdu(sockfd);
		if(NULL == rsppdu)
		{
			printf("recv_avepdu failed\n");
			break;
		}

		printf("The ave is %.2f\n",*(float *)rsppdu->rands);
		destroy_avepdu(rsppdu);
		rsppdu = NULL;
	}

	return 0;
}

int input_count()
{
	int cnt = 0;

	printf("Please input a number:\n");
	scanf("%d",&cnt);

	while(getchar() != '\n')
	{
	}

	return cnt;
}

int create_tcp_client_socket(char *ipaddr,unsigned short port)
{
        int sockfd = -1;
        int ret = 0;
        struct sockaddr_in servaddr;

        sockfd = socket(AF_INET,SOCK_STREAM,0);
        if(sockfd < 0)
        {
                printf("call socket function failed\n");
                return -1;
        }

        bzero(&servaddr,sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(port);
        inet_aton(ipaddr,&servaddr.sin_addr);

        ret = connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
        if(ret < 0)
        {
                close(sockfd);
                sockfd = -1;
                printf("connect server failed\n");
                return ret;
        }

        return sockfd;
}

