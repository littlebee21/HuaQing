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


int handle_client_data(int datafd);
int server_main_loop(int servfd)
{
	int datafd = -1;
	fd_set rfds;
	fd_set oldrfds;
	int ret = 0;
	int i = 0;

	FD_ZERO(&oldrfds);
	FD_SET(servfd,&oldrfds);

        while(1)
        {
		memcpy(&rfds,&oldrfds,sizeof(fd_set));
		ret = select(FD_SETSIZE,&rfds,NULL,NULL,NULL);
		if(ret < 0)
		{
			if(errno == EINTR)
			{
				continue;
			}
			else
			{
				perror("select failed:\n");
				break;
			}
		}

		for(i = 0;i < FD_SETSIZE;i++)
		{
			if(FD_ISSET(i,&rfds))
			{
				if(i == servfd)
				{//处理连接请求的描述符中有数据可读（意味着有新客户端和本服务器通过三路握手建立好了连接）
                			datafd = accept(servfd,NULL,NULL);
			                if(datafd < 0)
        			        {
                		                perror("accept failed:");
                        		        break;
	                		}
					FD_SET(datafd,&oldrfds);
				}
				else
				{//发现数据交互用的描述符中有数据可读（意味着有某个客户端发来了新的数据）
					if(handle_client_data(i) < 0)
					{
						close(i);
						FD_CLR(i,&oldrfds);
					}
				}
			}//end of if(FD_ISSET(i,&rfds))
		}//end of for(i = 0;i < FD_SETSIZE;i++)
        }//end of  while(1)

        return 0;

}

float get_ave(int *pi,int cnt);
/*
 * 返回0表示处理客户端发过来的数据正常
 * 返回-1表示出错，返回后应该关闭描述符
 * 返回1表示处理客户端发过来的数据不正常，但无需关闭描述符，可继续与对应客户端进行下一轮数据交互
 * */
int handle_client_data(int datafd)
{
	int ret = 0;
	struct avepdu * pdu = NULL;
	struct avepdu * rsppdu = NULL;

	do
	{
		/*接收pdu*/
		pdu = recv_avepdu(datafd);
		if(NULL == pdu)
		{
			printf("call recv_avepdu failed\n");
			ret = -1;
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
			ret = -1;
			break;
		}
	}while(0);

	return ret;
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
