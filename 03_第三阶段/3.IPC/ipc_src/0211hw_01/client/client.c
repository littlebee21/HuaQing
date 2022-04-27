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
	wfd = open(FIFO_C_TO_S,O_WRONLY);
	if(wfd < 0)
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
	rfd = open(FIFO_S_TO_C,O_RDONLY);
	if(rfd < 0)
	{
		close(wfd);
		wfd = -1;
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

int input_select();
int input_filename(char *pout,int cnt);
int print_filecontent(char *pcontent,int cnt);
int main_loop(int wfd,int rfd)
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
				ret = send_filepdu(wfd,reqpdu);
				destroy_filepdu(reqpdu);
				reqpdu = NULL;
				if(ret != 0)
				{
					printf("send get file content pdu failed\n");
					isexit = 1;
					break;
				}

				/*获取回应*/
				rsppdu = recv_filepdu(rfd);

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
				ret = send_filepdu(wfd,reqpdu);
				destroy_filepdu(reqpdu);
				reqpdu = NULL;
				if(ret != 0)
				{
					printf("send get file length pdu failed\n");
					isexit = 1;
					break;
				}

				/*获取回应*/
				rsppdu = recv_filepdu(rfd);

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
