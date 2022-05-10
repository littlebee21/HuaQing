#include "protocol.h"

struct rands_pdu *create_ave_req_pdu(int cnt)
{
	int tlen = 0;
	struct rands_pdu *pdu = NULL;
	int i = 0;

	tlen = sizeof(int) * 2 + cnt * sizeof(int);
	pdu = (struct rands_pdu *)malloc(tlen);
	if(NULL == pdu)
	{
		printf("Malloc rands_pdu failed\n");
		return NULL;
	}
	memset(pdu,0,tlen);

	pdu->len = cnt * sizeof(int);
	pdu->type =  PDU_TYPE_AVE_REQ;

	for(i =0;i < cnt;i++)
	{
		*((int *)pdu->buf + i) = rand() % 1000;
	}

	return pdu;
}
struct rands_pdu *create_max_req_pdu(int cnt)
{
	struct rands_pdu *pdu = create_ave_req_pdu(cnt);
	if(pdu != NULL)
	{
		pdu->type = PDU_TYPE_MAX_REQ;
	}
	else
	{
		printf("create_max_req_pdu failed\n");
	}
	return pdu;
}
struct rands_pdu *create_min_req_pdu(int cnt)
{
	struct rands_pdu *pdu = create_ave_req_pdu(cnt);
	if(pdu != NULL)
	{
		pdu->type = PDU_TYPE_MIN_REQ;
	}
	else
	{
		printf("create_max_req_pdu failed\n");
	}
	return pdu;
}

static float get_rands_ave(int *prand,int num)
{
        float sum = 0.0;
        int i = 0;

        for(i = 0;i < num;i++)
        {
                sum += *(prand + i);
        }

        return sum/num;
}
static int get_rands_max(int *prand,int num)
{
        int i = 0;
	int ret = 0;

        for(i = 1;i < num;i++)
        {
		if(*(prand+i) > *(prand + ret))
		{
			ret = i;
		}
        }
        return ret;
}

static int get_rands_min(int *prand,int num)
{
        int i = 0;
	int ret = 0;

        for(i = 1;i < num;i++)
        {
		if(*(prand+i) < *(prand + ret))
		{
			ret = i;
		}
        }
        return ret;
}

struct rands_pdu *create_ave_rsp_pdu(int *pi,int cnt)
{
	int tlen = 0;
	struct rands_pdu *pdu = NULL;

	tlen = sizeof(int) * 2 + sizeof(float);
	pdu = (struct rands_pdu *)malloc(tlen);
	if(NULL == pdu)
	{
		printf("Malloc rands_pdu failed\n");
		return NULL;
	}
	memset(pdu,0,tlen);

	pdu->len = sizeof(float);
	pdu->type = PDU_TYPE_AVE_RSP;

	*(float *)pdu->buf = get_rands_ave(pi,cnt);
	return pdu;
}
struct rands_pdu *create_max_rsp_pdu(int *pi,int cnt)
{
	int tlen = 0;
	struct rands_pdu *pdu = NULL;

	tlen = sizeof(int) * 2 + sizeof(float);
	pdu = (struct rands_pdu *)malloc(tlen);
	if(NULL == pdu)
	{
		printf("Malloc rands_pdu failed\n");
		return NULL;
	}
	memset(pdu,0,tlen);

	pdu->len = sizeof(float);
	pdu->type = PDU_TYPE_MAX_RSP;

	*(int *)pdu->buf = *(pi+get_rands_max(pi,cnt));
	return pdu;
}
struct rands_pdu *create_min_rsp_pdu(int *pi,int cnt)
{
	int tlen = 0;
	struct rands_pdu *pdu = NULL;

	tlen = sizeof(int) * 2 + sizeof(float);
	pdu = (struct rands_pdu *)malloc(tlen);
	if(NULL == pdu)
	{
		printf("Malloc rands_pdu failed\n");
		return NULL;
	}
	memset(pdu,0,tlen);

	pdu->len = sizeof(float);
	pdu->type = PDU_TYPE_MIN_RSP;

	*(int *)pdu->buf = *(pi+get_rands_min(pi,cnt));
	return pdu;
}

int send_rands_pdu(int fd,struct rands_pdu *pdu)
{
	int sndlen = 0;
	int ret = 0;

	sndlen = sizeof(int)*2 + pdu->len;
	ret = send(fd,pdu,sndlen,0);
	if(ret != sndlen)
	{
		printf("send_rands_pdu failed\n");
		return -1;
	}

	return 0;
}
struct rands_pdu *recv_rands_pdu(int fd)
{
	int len = 0;
	int tlen = 0;
	int ret = 0;
	struct rands_pdu *pdu = NULL;
	
	ret = recv(fd,&len,sizeof(int),0);
	if(ret <= 0)
	{
		printf("recv len failed\n");
		return NULL;
	}

	tlen = len + sizeof(int) * 2;

	pdu = (struct rands_pdu *)malloc(tlen);
	if(NULL == pdu)
	{
		printf("Malloc rands_pdu failed\n");
		return NULL;
	}
	memset(pdu,0,tlen);

	pdu->len = len;
	ret = recv(fd,&pdu->type,len + sizeof(int),0);
	if(ret <= 0)
	{
		free(pdu);
		pdu = NULL;
		printf("recv data failed\n");
		return NULL;
	}

	return pdu;
}


int destroy_rands_pdu(struct rands_pdu *pdu)
{
	if(pdu != NULL)
	{
		free(pdu);
		pdu = NULL;
	}

	return 0;
}

