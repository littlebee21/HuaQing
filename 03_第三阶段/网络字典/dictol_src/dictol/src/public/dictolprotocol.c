#include "dictolpublic.h"

struct DictOLPDU *CreateRegisterREQPDU(char *name,char *password)
{
    long len = 0;
    struct DictOLPDU *pstPDU = NULL;
    /*函数的输入参数做合法性检查*/
    if(NULL == name || NULL == password)
    {
	    PrintPublicError("Input Param is invalid\n");
    	return NULL;
    }
    
    /*计算总的空间的大小*/
    len = DICTOL_PDU_HEADER_SIZE + NAME_LEN + PASS_LEN;
        
    /*分配空间*/
    pstPDU = (struct DictOLPDU *)malloc(len);
    if(NULL == pstPDU)
    {
		PrintPublicError("Malloc Failed\n");
		return NULL;
    }
    memset(pstPDU,0,len);
    
    /*向被分配的空间填值*/
    pstPDU->size = len;
    pstPDU->type = DICTOL_PDU_TYPE_REG_REQ;

    strncpy(pstPDU->buf,name,NAME_LEN - 1);
    strncpy(pstPDU->buf+NAME_LEN,password,PASS_LEN - 1);
    
    /*返回被分配空间的首地址*/
    return pstPDU;
}

struct DictOLPDU *CreateLoginREQPDU(char *name,char *password)
{
    struct DictOLPDU *pstPDU = NULL;

    pstPDU = CreateRegisterREQPDU(name,password);
    if(pstPDU != NULL)
    {
        pstPDU->type = DICTOL_PDU_TYPE_LOGIN_REQ;
    }
    
    return pstPDU;
}


static struct DictOLPDU *CreateIntPDU(int type,int value)
{
    long len = 0;
    struct DictOLPDU *pstPDU = NULL;

    /*函数的输入参数做合法性检查*/
    if(type != DICTOL_PDU_TYPE_REG_RSP && type != DICTOL_PDU_TYPE_LOGIN_RSP)
    {
    	PrintPublicError("Input Param is invalid\n");
    	return NULL;
    }
    
    /*计算总的空间的大小*/
    len = DICTOL_PDU_HEADER_SIZE + sizeof(int);
        
    /*分配空间*/
    pstPDU = (struct DictOLPDU *)malloc(len);
    if(NULL == pstPDU)
    {
		PrintPublicError("Malloc Failed\n");
		return NULL;
    }
    memset(pstPDU,0,len);
    
    /*向被分配的空间填值*/
    pstPDU->size = len;
    pstPDU->type = type;
    *((int *)pstPDU->buf) = value;
    
    /*返回被分配空间的首地址*/
    return pstPDU;
}

struct DictOLPDU *CreateRegisterRSPPDU(int value)
{
    return CreateIntPDU(DICTOL_PDU_TYPE_REG_RSP,value);
}

struct DictOLPDU *CreateLoginRSPPDU(int value)
{
    return CreateIntPDU(DICTOL_PDU_TYPE_LOGIN_RSP,value);
}

static struct DictOLPDU *CreateStringPDU(int type,const char *str)
{
    long len = 0;
    struct DictOLPDU *pstPDU = NULL;

    /*函数的输入参数做合法性检查*/
    if((type != DICTOL_PDU_TYPE_QUERYWORD_REQ && 
        type != DICTOL_PDU_TYPE_QUERYWORD_RSP && 
        type != DICTOL_PDU_TYPE_HISTORY_RSP) ||
       NULL == str)
    {
    	PrintPublicError("Input Param is invalid\n");
    	return NULL;
    }
    
    /*计算总的空间的大小*/
    len = DICTOL_PDU_HEADER_SIZE + strlen(str) + 1;
        
    /*分配空间*/
    pstPDU = (struct DictOLPDU *)malloc(len);
    if(NULL == pstPDU)
    {
		PrintPublicError("Malloc Failed\n");
		return NULL;
    }
    memset(pstPDU,0,len);
    
    /*向被分配的空间填值*/
    pstPDU->size = len;
    pstPDU->type = type;
    strcpy(pstPDU->buf,str);
    
    /*返回被分配空间的首地址*/
    return pstPDU;
}

struct DictOLPDU *CreateQueryWordREQPDU(char *word)
{
    return CreateStringPDU(DICTOL_PDU_TYPE_QUERYWORD_REQ,word);
}

struct DictOLPDU *CreateQueryWordRSPPDU(char *explain)
{
    return CreateStringPDU(DICTOL_PDU_TYPE_QUERYWORD_RSP,explain);
}

struct DictOLPDU *CreateHistoryRSPPDU(char *history)
{
    return CreateStringPDU(DICTOL_PDU_TYPE_HISTORY_RSP,history);
}

struct DictOLPDU *CreateHistoryREQPDU()
{
    long len = 0;
    struct DictOLPDU *pstPDU = NULL;
    
    /*计算总的空间的大小*/
    len = DICTOL_PDU_HEADER_SIZE;
        
    /*分配空间*/
    pstPDU = (struct DictOLPDU *)malloc(len);
    if(NULL == pstPDU)
    {
		PrintPublicError("Malloc Failed\n");
		return NULL;
    }
    memset(pstPDU,0,len);
    
    /*向被分配的空间填值*/
    pstPDU->size = len;
    pstPDU->type = DICTOL_PDU_TYPE_HISTORY_REQ;
    
    /*返回被分配空间的首地址*/
    return pstPDU;
}




int DestroyDictOLPDU(struct DictOLPDU * pstPDU)
{
    if(pstPDU != NULL)
    {
        free(pstPDU);
    }
    return 0;
}

int SendPDU(int fd,struct DictOLPDU *pstPDU)
{
    int ret = 0;
    if(fd < 0 || NULL == pstPDU)
    {
    	PrintPublicError("Input Param is invalid\n");
    	return -1;
    }
	
    ret = MyWrite(fd,pstPDU,pstPDU->size);
    if(ret != pstPDU->size)
    {
        PrintPublicError("Send PDU Failed\n");
        return -1;
    }

    return 0;
}

struct DictOLPDU * RecvPDU(int fd)
{
    int len = 0;
    int ret = 0;
    struct DictOLPDU *pstPDU = NULL;

    if(fd < 0)
    {
        PrintPublicError("Input Param is invalid\n");
        return NULL;
    }

    ret = MyRead(fd,&len,sizeof(int));
    if(ret != sizeof(int) || len <= 0)
    {
        PrintPublicError("read size error\n");
        return NULL;
    }

    pstPDU = (struct DictOLPDU *)malloc(len);
    if(NULL == pstPDU)
    {
        PrintPublicError("Malloc Failed\n");
        return NULL;
    }
    memset(pstPDU,0,len);

    pstPDU->size = len;
    ret = MyRead(fd,&pstPDU->type,len - sizeof(int));
    if(ret != len - sizeof(int))
    {
        PrintPublicError("receive failed\n");
        free(pstPDU);
        pstPDU = NULL;
    }

    return pstPDU;
}

