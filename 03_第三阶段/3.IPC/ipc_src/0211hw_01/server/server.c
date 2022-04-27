#include "filepdu.h"

int main_loop(int wfd,int rfd);

int main(int argc,char *argv[])
{
	int wfd = -1;
	int rfd = -1;
	int ret = 0;

	/*创建打开c-s管道*/
	ret = access(FIFO_C_TO_S,F_OK);
	if(ret < 0)
	{
		ret = mkfifo(FIFO_C_TO_S,0666);
		if(ret < 0)
		{
			printf("mkfifo c-s failed\n");
			return 1;
		}
	}
	rfd = open(FIFO_C_TO_S,O_RDONLY);
	if(rfd < 0)
	{
		printf("open c-s fifo failed\n");
		return 2;
	}

	/*创建打开s-c管道*/
	ret = access(FIFO_S_TO_C,F_OK);
	if(ret < 0)
	{
		ret = mkfifo(FIFO_S_TO_C,0666);
		if(ret < 0)
		{
			printf("mkfifo s-c failed\n");
			return 3;
		}
	}
	wfd = open(FIFO_S_TO_C,O_WRONLY);
	if(wfd < 0)
	{
		close(rfd);
		rfd = -1;
		printf("open s-c fifo failed\n");
		return 4;
	}

	main_loop(wfd,rfd);

	/*关闭描述符*/
	close(wfd);
	wfd = -1;
	close(rfd);
	rfd = -1;
	return 0;
}

int main_loop(int wfd,int rfd)
{
	int ret = 0;
	struct filepdu *reqpdu = NULL;
	struct filepdu *rsppdu = NULL;
	int isbreak = 0;

	while(1)
	{
		reqpdu = recv_filepdu(rfd);
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
				ret = send_filepdu(wfd,rsppdu);
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
				ret = send_filepdu(wfd,rsppdu);
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

	return 0;
}

