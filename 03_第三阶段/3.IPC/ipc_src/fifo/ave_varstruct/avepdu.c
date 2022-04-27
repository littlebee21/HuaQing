#include "avepdu.h"

/*本程序协议数据组织相关的代码*/

static struct avepdu *alloc_avepdu(int cnt)
{
	struct avepdu *pdu = NULL;

	/*分配cnt+1个整数的内存空间*/
	pdu = (struct avepdu *)malloc((cnt+1)*sizeof(int));
	if(NULL == pdu)
	{
		perror("Malloc for avepdu failed\n");
		return NULL;
	}
	memset(pdu,0,(cnt+1) * sizeof(int));

	/*cnt赋值给第一个成员*/
	pdu->n = cnt;

	/*返回动态空间的首地址*/
	return pdu;
}
struct avepdu *create_avepdu(int cnt)
{
	struct avepdu *pdu = NULL;
	int i = 0;

	/*分配cnt+1个整数的内存空间*/
	pdu = alloc_avepdu(cnt);
	if(pdu == NULL)
	{
		printf("create avepdu failed\n");
		return NULL;
	}

	/*产生cnt个随机数*/
	for(i = 0;i < cnt;i++)
	{
		*(pdu->rands + i) = rand() % 100;
	}

	/*返回动态空间的首地址*/
	return pdu;
}

int destroy_avepdu(struct avepdu *p_pdu)
{
	if(p_pdu != NULL)
	{
		free(p_pdu);
		p_pdu = NULL;
	}

	return 0;
}

int send_avepdu(int fd,struct avepdu *p_pdu)
{
	int ret = 0;
	int len = 0;

	len = (p_pdu->n + 1) *sizeof(int);
	ret = write(fd,p_pdu,len);
	if(ret != len)
	{
		printf("send avepdu failed,ret=%d\n",ret);
		return -1;
	}

	return 0;
}

struct avepdu *recv_avepdu(int fd)
{
	int cnt = 0;
	int ret = 0;
	int len = 0;
	struct avepdu *pdu = NULL;
	
	ret = read(fd,&cnt,sizeof(int));
	if(ret != sizeof(int))
	{
		printf("read count failed,ret=%d\n",ret);
		return NULL;
	}

	pdu = alloc_avepdu(cnt);
	if(pdu == NULL)
	{
		printf("alloc avepdu failed in recv_avepdu\n");
		return NULL;
	}

	len = cnt *sizeof(int);
	ret = read(fd,pdu->rands,len);
	if(ret != len)
	{
		printf("read cnt-rands failed,ret=%d\n",ret);
		return NULL;
	}

	return pdu;
}






