#include "avepdu.h"

int server_main_loop(int servfd);
int create_tcp_server_socket(char *ipaddr,unsigned short port);
int main(int argc,char *argv[])
{

	int servfd = -1;
        int iport = -1;

        if(argc < 3)
        {
                printf("The argument is too few\n");
                return 1;
        }

        sscanf(argv[2],"%d",&iport);
        if(iport < 0 || iport > 0xFFFF)
        {
                printf("The port is invalid\n");
                return 2;
        }

        servfd = create_tcp_server_socket(argv[1],(unsigned short)iport);
        if(servfd < 0)
        {
                printf("create_tcp_server_socket failed\n");
                return 3;
        }


	server_main_loop(servfd);

	close(servfd);
	servfd = -1;

	return 0;
}

int create_tcp_server_socket(char *ipaddr,unsigned short port)
{
        int servfd = -1;
        struct sockaddr_in servaddr;
        int ret = 0;

        servfd = socket(AF_INET,SOCK_STREAM,0);
        if(servfd < 0)
        {
                printf("call socket function failed\n");
                return -1;
        }

        bzero(&servaddr,sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(port);
        inet_aton(ipaddr,&servaddr.sin_addr);

        ret = bind(servfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
        ret += listen(servfd,6);
        if(ret < 0)
        {
                close(servfd);
                servfd = -1;
                perror("bind or listen failed:");
                return -1;
        }

        return servfd;
}


void * handle_client_data(void *arg);
int server_main_loop(int servfd)
{
	int datafd = -1;
	pthread_t tid;
	int ret = 0;

        while(1)
        {
                datafd = accept(servfd,NULL,NULL);
                if(datafd < 0)
                {
                        if(errno == EINTR)
                        {//本次错误是信号引起，可会忽略本错误
                                continue;
                        }
                        else
                        {
                                perror("accept failed:");
                                break;
                        }
                }

		ret = pthread_create(&tid,NULL,handle_client_data,(void *)(long)datafd);
		if(ret != 0)	
		{
			close(datafd);
			datafd = -1;
			continue;
		}
        }

        return 0;

}

float get_ave(int *pi,int cnt);
void * handle_client_data(void *arg)
{
	int datafd = (int)(long)arg;
	int ret = 0;
	struct avepdu * pdu = NULL;
	struct avepdu * rsppdu = NULL;

	pthread_detach(pthread_self());

	while(1)
	{
		/*接收pdu*/
		pdu = recv_avepdu(datafd);
		if(NULL == pdu)
		{
			printf("call recv_avepdu failed\n");
			break;
		}

		/*计算均值并输出*/
		rsppdu = create_ave_rsp_pdu(get_ave(pdu->rands,pdu->n));

		/*销毁pdu*/
		destroy_avepdu(pdu);
		pdu = NULL;

		/*发送rsp-pdu*/
		ret = send_avepdu(datafd,rsppdu);
		destroy_avepdu(rsppdu);
		rsppdu = NULL;
		if(ret != 0)
		{
			printf("send_avepdu failed\n");
			break;
		}
	}
	close(datafd);
	datafd = -1;

	return NULL;
}

float get_ave(int *pi,int cnt)
{
	float sum = 0.0f;
	int i = 0;

	for(i = 0;i < cnt;i++)
	{
		sum += *(pi+i);
	}

	return sum / cnt;
}
