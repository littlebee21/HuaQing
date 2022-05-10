#include "filepdu.h"

int create_tcp_server_socket(char *ipaddr,unsigned short port);
int main_loop(int servfd);

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


	main_loop(servfd);

	/*关闭描述符*/
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


int handle_client(int datafd);
int main_loop(int servfd)
{
	int datafd = -1;
	int ret = 0;
	int i = 0;
	fd_set oldrfds;//用来保存让select监控可读的描述符们
	fd_set rfds;//作为select第二个参数用的，每次调用select前从oldrfds中copy待监控的描述符们

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
				perror("select failed:");
				break;
			}
		}

		for(i = 0;i < FD_SETSIZE;i++)
		{
			if(FD_ISSET(i,&rfds))
			{
				if(i == servfd)
				{//此时i为服务端处理TCP连接请求的socket描述符
					datafd = accept(i,NULL,NULL);
					if(datafd < 0)
					{
						perror("accept failed:");
					}
					else
					{
						FD_SET(datafd,&oldrfds);
					}
				}
				else
				{//此时i为accept函数返回的、用来与对应客户端进行数据交互的socket描述符
					if(0 > handle_client(i))
					{
						close(i);
						FD_CLR(i,&oldrfds);
					}
				}
			}//end of if(FD_ISSET(i,&rfds))
		}//end of for(i = 0;i < FD_SETSIZE;i++)
	}//end of while(1)
	
	return 0;
}

int handle_client(int datafd)
{
	int ret = 0;
	struct filepdu *reqpdu = NULL;
	struct filepdu *rsppdu = NULL;
	int isbreak = 0;


	do
	{
		reqpdu = recv_filepdu(datafd);
		if(NULL == reqpdu)
		{
			printf("recv req failed\n");
			ret = -1;
			break;
		}

		switch(reqpdu->type)
		{
			case TYPE_GET_CONTENT_REQ:
				rsppdu = create_getcontent_response(reqpdu->data);
				destroy_filepdu(reqpdu);
				reqpdu = NULL;
				if(NULL == rsppdu)
				{
					printf("create content rsp failed\n");
					isbreak = 1;
					ret = -1;
					break;
				}
				ret = send_filepdu(datafd,rsppdu);
				destroy_filepdu(rsppdu);
				rsppdu = NULL;
				if(ret != 0)
				{
					printf("send content rsp failed\n");
					isbreak = 1;
					ret = -1;
					break;
				}
				break;
			case TYPE_GET_FILELEN_REQ:
				rsppdu = create_getlength_response(reqpdu->data);
				destroy_filepdu(reqpdu);
				reqpdu = NULL;
				if(NULL == rsppdu)
				{
					printf("create length rsp failed\n");
					isbreak = 1;
					ret = -1;
					break;
				}
				ret = send_filepdu(datafd,rsppdu);
				destroy_filepdu(rsppdu);
				rsppdu = NULL;
				if(ret != 0)
				{
					printf("send length rsp failed\n");
					isbreak = 1;
					ret = -1;
					break;
				}
				break;
			default:
				printf("The req is not supported\n");
				destroy_filepdu(reqpdu);
				reqpdu = NULL;
				ret = 1;
				break;
		}
		if(isbreak)
		{
			break;
		}
	}while(0);

	if(ret < 0)
	{
		close(datafd);
		datafd = -1;
	}

	return ret;
}

