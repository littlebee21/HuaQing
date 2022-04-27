#ifndef DICTOL_PROTOCOL_H
#define DICTOL_PROTOCOL_H

#include <unistd.h>
#include <errno.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 24
#define PASS_LEN 24

#define WORD_LEN 32

/*PDU种类数字对应的枚举常量*/
enum ENUM_DICTOL_PDU_TYPE
{
	DICTOL_PDU_TYPE_REG_REQ = 1,
	DICTOL_PDU_TYPE_REG_RSP,
	DICTOL_PDU_TYPE_LOGIN_REQ,
	DICTOL_PDU_TYPE_LOGIN_RSP,
	DICTOL_PDU_TYPE_QUERYWORD_REQ,
	DICTOL_PDU_TYPE_QUERYWORD_RSP,
	DICTOL_PDU_TYPE_HISTORY_REQ,
	DICTOL_PDU_TYPE_HISTORY_RSP
};


/*struct DictOLPDU成员作用描述:
	size:PDU数据总字节数
	type:表示协议数据的种类，相应数字对应相应种类
		1.注册请求 2.注册回应  
		3.登录请求 4.登录回应 
		5.查词请求 6.查词回应 
		7.历史请求 8.历史回应
	buf:对应种类PDU使用的实际数据，不同的种类数据组织形式不一样:
		注册请求、登录请求：NAME_LEN个字节的用户名+PASS_LEN个字节的密码
		注册回应、登录回应：为sizeof(int)个字节的处理结果，其中0表示成功，其它值为错误，不同值可以表示不同的错误号
		查词请求：'\0'结尾的字符串，字符串内容为所要查询的单词
		查词回应：'\0'结尾的字符串，字符串内容为单词的释义，"Not Found"表示未找到单词
		历史请求：没有此部分，此时size为sizeof(long) * 2
		历史回应：'\0'结尾的字符串，字符串内容为'@'分隔的多条历史记录，每条历史记录用#分隔时间和单词
*/
struct  DictOLPDU
{
	int size;
	int type;
   	char buf[1];
};


#define DICTOL_PDU_HEADER_SIZE  (sizeof(int) * 2)
#define QUERY_WORD_ERR_STR "Not Found"
#define QUERY_HISTORY_ERR_STR "No History"

struct DictOLPDU *CreateRegisterREQPDU(char *name,char *password); 
struct DictOLPDU *CreateRegisterRSPPDU(int value); 
struct DictOLPDU *CreateLoginREQPDU(char *name,char *password); 
struct DictOLPDU *CreateLoginRSPPDU(int value); 
struct DictOLPDU *CreateQueryWordREQPDU(char *word); 
struct DictOLPDU *CreateQueryWordRSPPDU(char *explain); 
struct DictOLPDU *CreateHistoryREQPDU(); 
struct DictOLPDU *CreateHistoryRSPPDU(char *history); 
    
struct DictOLPDU * RecvPDU(int fd);
int DestroyDictOLPDU(struct DictOLPDU * pstPDU);//RecvPDU函数和所有的Create函数均有动态分配，本函数负责释放

int SendPDU(int fd,struct DictOLPDU *pstPDU);

#endif
