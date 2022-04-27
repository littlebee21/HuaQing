#include "filepdu.h"

static struct filepdu *create_filepdu_bytype(int len,int type)
{
	struct filepdu *pdu = NULL;

	if(len <= 0 || type < 0 || type > 4)
	{
		printf("Input param is invalid\n");
		return NULL;
	}

	pdu = (struct filepdu *)malloc(len);
	if(NULL == pdu)
	{
		printf("Malloc failed,in create_filepdu_bytype\n");
		return NULL;
	}
	memset(pdu,0,len);

	pdu->len = len;
	pdu->type = type;

	return pdu;
}

struct filepdu *create_getcontent_request(char *filename)
{
	int len = 0;
	struct filepdu *pdu = NULL;

	/*计算本PDU的总字节数*/
	len = 2 * sizeof(int) + strlen(filename) + 1;

	/*创建*/
	pdu = create_filepdu_bytype(len,TYPE_GET_CONTENT_REQ);
	if(NULL == pdu)
	{
		printf("call create_getcontent_request failed\n");
		return pdu;
	}

	/*填data*/
	strcpy(pdu->data,filename);

	return pdu;
}

struct filepdu *create_getlength_request(char *filename)
{
	int len = 0;
	struct filepdu *pdu = NULL;

	/*计算本PDU的总字节数*/
	len = 2 * sizeof(int) + strlen(filename) + 1;

	/*创建*/
	pdu = create_filepdu_bytype(len,TYPE_GET_FILELEN_REQ);
	if(NULL == pdu)
	{
		printf("call create_getcontent_request failed\n");
		return pdu;
	}

	/*填data*/
	strcpy(pdu->data,filename);

	return pdu;
}

struct filepdu *create_getcontent_response(char *filename)
{
	struct stat meta;
	int ret = 0;
	int filelen = 0;
	int rspval = 0;
	int pdulen = 0;
	struct filepdu *pdu = NULL;

	/*获取文件大小*/
	ret = stat(filename,&meta);

	if(ret < 0)
	{//错误情况1
		rspval = 1;
	}
	else
	{
		if((meta.st_mode & S_IFMT) == S_IFREG && meta.st_size > 0)
		{//正确情况
			filelen = meta.st_size;
		}
		else
		{//错误情况2 3
			if((meta.st_mode & S_IFMT) != S_IFREG)
			{
				rspval = 2;
			}
			else
			{
				rspval = 3;
			}
		}
	}

	if(rspval == 0)
	{//创建正确的回应PDU
		pdulen = 3 * sizeof(int) + filelen;
		int fd = -1;

		fd = open(filename,O_RDONLY);
		if(fd < 0)
		{
			rspval = 4;
		}
		else
		{
			pdu = create_filepdu_bytype(pdulen,TYPE_GET_CONTENT_RSP);
			if(pdu == NULL)
			{
				rspval = 5;
			}
			else
			{
				ret = read(fd,pdu->data + 4,filelen); 
				close(fd);
				fd = -1;
				if(ret != filelen)
				{
					rspval = 6;
					destroy_filepdu(pdu);
					pdu = NULL;
				}
				else
				{//所有都正常
					*(int *)pdu->data = rspval;
				}
			}
		}
	}
	if(rspval != 0)
	{//创建错误的回应PDU
		pdulen = 3 * sizeof(int);
		pdu = create_filepdu_bytype(pdulen,TYPE_GET_CONTENT_RSP);
		if(pdu == NULL)
		{
			printf("call create_getcontent_response failed\n");
			return NULL;
		}
		*(int *)pdu->data = rspval;
	}
	return pdu;
}

struct filepdu *create_getlength_response(char *filename)
{
	struct stat meta;
	int ret = 0;
	int filelen = 0;
	int rspval = 0;
	int pdulen = 0;
	struct filepdu *pdu = NULL;

	/*获取文件大小*/
	ret = stat(filename,&meta);

	if(ret < 0)
	{//错误情况1
		rspval = 1;
	}
	else
	{
		if((meta.st_mode & S_IFMT) == S_IFREG && meta.st_size > 0)
		{//正确情况
			filelen = meta.st_size;
		}
		else
		{//错误情况2 3
			if((meta.st_mode & S_IFMT) != S_IFREG)
			{
				rspval = 2;
			}
			else
			{
				rspval = 3;
			}
		}
	}
	if(rspval == 0)
	{
		pdulen = 4 * sizeof(int);
		pdu = create_filepdu_bytype(pdulen,TYPE_GET_FILELEN_RSP);
		if(pdu == NULL)
		{
			printf("call create_getlength_response failed\n");
		}
		else
		{
			*(int *)pdu->data = rspval;
			*(int *)(pdu->data + sizeof(int))= filelen;
		}
	}
	else
	{
		pdulen = 3 * sizeof(int);
		pdu = create_filepdu_bytype(pdulen,TYPE_GET_FILELEN_RSP);
		if(pdu == NULL)
		{
			printf("call create_getlength_response failed\n");
		}
		else
		{
			*(int *)pdu->data = rspval;
		}
	}

	return pdu;
}

int send_filepdu(int fd,struct filepdu *pdu)
{
	int ret = 0;

	ret = write(fd,pdu,pdu->len);
	if(ret != pdu->len)
	{
		printf("send filpdu failed,ret=%d\n",ret);
		return -1;
	}

	return 0;
}

struct filepdu *recv_filepdu(int fd)
{
	int len = 0;
	int ret = 0;
	struct filepdu *pdu = NULL;

	ret = read(fd,&len,sizeof(int));
	if(ret != sizeof(int))
	{
		printf("recv pdu len failed\n");
		return NULL;
	}

	pdu = create_filepdu_bytype(len,0);
	if(NULL == pdu)
	{
		printf("call recv_filepdu failed\n");
		return NULL;
	}

	ret = read(fd,&pdu->type,len - sizeof(int));
	if(ret != len - sizeof(int))
	{
		printf("recv pdu data failed\n");
		return NULL;
	}

	return pdu;
}

int destroy_filepdu(struct filepdu *pdu)
{
	if(pdu != NULL)
	{
		free(pdu);
		pdu = NULL;
	}

	return 0;
}


