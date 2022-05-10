#include "filepdu.h"

int create_tcp_client_socket(char *ipaddr,unsigned short port);
int main_loop(int sockfd);

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

	main_loop(sockfd);

	/*关闭描述符*/
	close(sockfd);
	sockfd = -1;
	return 0;
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


int input_select();
int input_filename(char *pout,int cnt);
int print_filecontent(char *pcontent,int cnt);
int main_loop(int sockfd)
{
	int ret = 0;
	int op = -1;
	int isexit = 0;
	char filename[40] = "";
	struct filepdu *reqpdu = NULL;
	struct filepdu *rsppdu = NULL;

	while(1)
	{
		/*选择操作*/
		op = input_select();
	
		/*完成相应操作*/
		switch(op)
		{
			case 1://获取文件内容
				/*输入文件名*/
				input_filename(filename,40);

				/*创建PDU*/
				reqpdu = create_getcontent_request(filename);
				if(NULL == reqpdu)
				{
					printf("create get file content pdu failed\n");
					isexit = 1;
					break;
				}

				/*发送请求*/
				ret = send_filepdu(sockfd,reqpdu);
				destroy_filepdu(reqpdu);
				reqpdu = NULL;
				if(ret != 0)
				{
					printf("send get file content pdu failed\n");
					isexit = 1;
					break;
				}

				/*获取回应*/
				rsppdu = recv_filepdu(sockfd);

				/*打印文件内容*/
				if(rsppdu != NULL && *(int *)rsppdu->data == 0)
				{
					print_filecontent(rsppdu->data+4,rsppdu->len - 3 * sizeof(int));
				}
				else
				{
					if(NULL == rsppdu)
					{
						printf("recv file content rsp failed\n");
						isexit = 1;
					}
					else
					{
						printf("Get file content failed,result-val= %d\n",*(int *)rsppdu->data);
					}
				}

				/*销毁回应pdu*/
				destroy_filepdu(rsppdu);
				rsppdu = NULL;
				break;
			case 2://获取文件大小
				/*输入文件名*/
				input_filename(filename,40);

				/*创建PDU*/
				reqpdu = create_getlength_request(filename);
				if(NULL == reqpdu)
				{
					printf("create get file length pdu failed\n");
					isexit = 1;
					break;
				}

				/*发送请求*/
				ret = send_filepdu(sockfd,reqpdu);
				destroy_filepdu(reqpdu);
				reqpdu = NULL;
				if(ret != 0)
				{
					printf("send get file length pdu failed\n");
					isexit = 1;
					break;
				}

				/*获取回应*/
				rsppdu = recv_filepdu(sockfd);

				/*打印文件大小*/
				if(rsppdu != NULL && *(int *)rsppdu->data == 0)
				{
					printf("The file length is %d\n",*(int *)(rsppdu->data + 4));
				}
				else
				{
					if(NULL == rsppdu)
					{
						printf("recv file length rsp failed\n");
						isexit = 1;
					}
					else
					{
						printf("Get file length failed,result-val= %d\n",*(int *)rsppdu->data);
					}
				}

				/*销毁回应pdu*/
				destroy_filepdu(rsppdu);
				rsppdu = NULL;
				break;
			case 0://退出
				isexit = 1;
				break;
			default://重新选择操作
				break;
		}
		if(isexit)
		{
			break;
		}
	}

	return 0;
}

int input_select()
{
	int op = -1;

	printf("Please input your select:\n");
	printf("1. Get File Content\n");
	printf("2. Get File Length\n");
	printf("0. Exit\n");

	scanf("%d",&op);

	while(getchar() != '\n')
	{
	}

	return op;
}

char *mygets(char *pout,int size);
int input_filename(char *pout,int cnt)
{
	printf("Please input a filename:\n");
	mygets(pout,cnt);

	return 0;
}

int print_filecontent(char *pcontent,int cnt)
{
	int i = 0;

	printf("The file content is:\n");
	for(i = 0;i < cnt;i++)
	{
		putchar(*(pcontent + i));
	}
	printf("\n");

	return 0;
}
