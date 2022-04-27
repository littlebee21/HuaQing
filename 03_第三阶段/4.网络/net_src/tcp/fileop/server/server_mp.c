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
	pid_t pid;


	signal(SIGCHLD,SIG_IGN);
	while(1)
	{
		datafd = accept(servfd,NULL,NULL);
		if(datafd < 0)
		{
			if(errno == EINTR)
			{
				continue;
			}
			else
			{
				printf("accept error\n");
				break;
			}
		}
		
		pid = fork();
		if(pid < 0)
		{
			close(datafd);
			datafd = -1;
			perror("fork error:");
			continue;
		}
		if(0 == pid)
		{
			close(servfd);
			servfd = -1;
			handle_client(datafd);
			exit(0);
		}
		else
		{
			close(datafd);
			datafd = -1;
		}
	}//while(1)
	
	return 0;
}

int handle_client(int datafd)
{
	int ret = 0;
	struct filepdu *reqpdu = NULL;
	struct filepdu *rsppdu = NULL;
	int isbreak = 0;

	while(1)
	{
		reqpdu = recv_filepdu(datafd);
		if(NULL == reqpdu)
		{
			printf("recv req failed\n");
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
					break;
				}
				ret = send_filepdu(datafd,rsppdu);
				destroy_filepdu(rsppdu);
				rsppdu = NULL;
				if(ret != 0)
				{
					printf("send content rsp failed\n");
					isbreak = 1;
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
					break;
				}
				ret = send_filepdu(datafd,rsppdu);
				destroy_filepdu(rsppdu);
				rsppdu = NULL;
				if(ret != 0)
				{
					printf("send length rsp failed\n");
					isbreak = 1;
					break;
				}
				break;
			default:
				printf("The req is not supported\n");
				destroy_filepdu(reqpdu);
				reqpdu = NULL;
				break;
		}
		if(isbreak)
		{
			break;
		}
	}

	close(datafd);
	datafd = -1;

	return 0;
}

