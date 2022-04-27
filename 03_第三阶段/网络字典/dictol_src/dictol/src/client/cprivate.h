#ifndef _DICTOL_CLIENT_PRIVATE_H
#define _DICTOL_CLIENT_PRIVATE_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictolpublic.h"

//客户端总控用结构体
struct DictOLClientCTL
{
   int sockfd;
   char acClientUserName[NAME_LEN];//登录后本客户端的用户名,将作为消息发送者
};


//注册功能接口
int Do_UserRegister(struct DictOLClientCTL *pstClient);

//登录功能接口
int Do_UserLogin(struct DictOLClientCTL *pstClient);

//查词功能接口
int Do_QueryWord(struct DictOLClientCTL *pstClient);

//历史记录查询功能接口
int Do_QueryHistory(struct DictOLClientCTL *pstClient);

//UI函数
int DisplayMainUI();
int DisplayFunctionUI();
char *InputUserName(char *pstr,int size,int firstflag);
char *InputPassword(char *pstr,int size,int firstflag);
char *InputWord(char *pstr,int size);
void DisplayExplain(char *word,char *explain);
void DisplayHistory(char *username,char *history);

void DisplayLoginRedoFailed();
void DisplayLoginExitFailed();
void DisplayLoginOK();
void DisplayRegisterRedoFailed();
void DisplayRegisterExitFailed();
void DisplayRegisterOK();

#endif
