#ifndef RAND_AVE_PROTOCOL_H
#define RAND_AVE_PROTOCOL_H
#include <unistd.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum pdu_type
{
	PDU_TYPE_AVE_REQ = 1,
	PDU_TYPE_MAX_REQ ,
	PDU_TYPE_MIN_REQ ,
	PDU_TYPE_AVE_RSP ,
	PDU_TYPE_MAX_RSP ,
	PDU_TYPE_MIN_RSP ,
};

struct rands_pdu
{
	int len;
	int type;//1.ave req  2.max req 3.min req 4.ave rsp 5.max rsp 6.min rsp 
	char buf[1];
};

struct rands_pdu *create_ave_req_pdu(int cnt);
struct rands_pdu *create_max_req_pdu(int cnt);
struct rands_pdu *create_min_req_pdu(int cnt);

struct rands_pdu *create_ave_rsp_pdu(int *pi,int cnt);
struct rands_pdu *create_max_rsp_pdu(int *pi,int cnt);
struct rands_pdu *create_min_rsp_pdu(int *pi,int cnt);

int send_rands_pdu(int fd,struct rands_pdu *pdu);
struct rands_pdu *recv_rands_pdu(int fd);

int destroy_rands_pdu(struct rands_pdu *pdu);



#endif
