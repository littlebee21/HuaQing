#include "sprivate.h"

static int HandleReg(int fd,sqlite3 *pDB,struct DictOLPDU *pstReqPDU);
static int HandleLogin(int fd,sqlite3 *pDB,struct DictOLPDU *pstReqPDU);
static int HandleQueryWord(int fd,sqlite3 *pDB,struct DictOLPDU *pstReqPDU,char *username);
static int HandleQueryHistory(int fd,sqlite3 *pDB,struct DictOLPDU *pstReqPDU,char *username);

int HandleClient(int fd,sqlite3 *pDB)
{
	int ret = 0;
	char curUserName[NAME_LEN] = "";
	int isLogin = 0;
	fd_set rfds;
	struct timeval timeout;
	struct DictOLPDU *pstReqPDU = NULL;

	while(1)
	{
		timeout.tv_sec = 5 * 60;
		timeout.tv_usec = 0;

		FD_ZERO(&rfds);
		FD_SET(fd,&rfds);
		ret = select(fd+1,&rfds,NULL,NULL,&timeout);
		if(ret < 0)
		{
			if(errno == EINTR)
			{
				PrintServerWarning("Select wake up by signal\n");
				continue;
			}
			else
			{
				PrintServerError("Select Failed\n");
				break;
			}
		}
		else if(0 == ret)
		{//timeout
			PrintServerError("Select Time Out\n");
			break;
		}
		if(FD_ISSET(fd,&rfds))
		{
			pstReqPDU = RecvPDU(fd);
			if(NULL == pstReqPDU)
			{
				PrintServerError("Receive PDU Failed\n");
				break;
			}
			switch(pstReqPDU->type)
			{
				case DICTOL_PDU_TYPE_REG_REQ:
					//return 0注册成功， < 0出错，> 0注册失败，但允许用户继续尝试注册或登录
					ret = HandleReg(fd,pDB,pstReqPDU);
					break;
				case DICTOL_PDU_TYPE_LOGIN_REQ:
					//return 0登录成功， < 0出错，> 0登录失败，但允许用户继续尝试注册或登录
					strcpy(curUserName,pstReqPDU->buf);
					ret = HandleLogin(fd,pDB,pstReqPDU);
					PrintServerInfo("HandleLogin return value is %d\n",ret);
					if(0 == ret)
					{
						isLogin = 1;
					}
					else
					{
						memset(curUserName,0,NAME_LEN);
					}
					break;
				default:
					PrintServerWarning("PDU received is invalid,it will be given up\n");
					DestroyDictOLPDU(pstReqPDU);
					pstReqPDU = NULL;
					break;
			}
			if(ret < 0)
			{
				PrintServerError("Handle PDU Failed\n");
				break;
			}
			if(isLogin)
			{
				break;
			}
		}
	}//end while(1)

	if(0 == isLogin || 0 == strcmp(curUserName,""))
	{//用户未能正常登录，不能使用查词、查询历史记录网络服务
		sqlite3_close(pDB);
        close(fd);
		PrintServerWarning("User can not login,it will disconnect tcp\n");
		return ret;
	}

	/*user can use dict net serve*/
	while(1)
	{
		pstReqPDU = RecvPDU(fd);
		if(NULL == pstReqPDU)
		{
			PrintServerError("Receive PDU Failed\n");
			break;
		}
		switch(pstReqPDU->type)
		{
			case DICTOL_PDU_TYPE_QUERYWORD_REQ:
				//return 0查词成功， < 0出错，> 0查词失败，但可继续使用下次服务
				ret = HandleQueryWord(fd,pDB,pstReqPDU,curUserName);
				break;
			case DICTOL_PDU_TYPE_HISTORY_REQ:
				//return 0查史成功， < 0出错，> 0查史失败，但可继续使用下次服务
				ret = HandleQueryHistory(fd,pDB,pstReqPDU,curUserName);
				break;
			default:
				PrintServerWarning("PDU received is invalid,it will be given up\n");
				DestroyDictOLPDU(pstReqPDU);
				pstReqPDU = NULL;
				break;
		}
	}

	UpdateUserFlag(pDB,curUserName,0);
	sqlite3_close(pDB);
    close(fd);
	return ret;
}

/*	
	处理注册请求，无论成功与否，销毁请求PDU
	return 0注册成功， < 0出错，> 0注册失败，但允许用户继续尝试注册或登录
*/
static int HandleReg(int fd,sqlite3 *pDB,struct DictOLPDU *pstReqPDU)
{
	int dbret = 0;
	int ret = 0;
	struct DictOLPDU *pstRspPDU = NULL;

	dbret = InsertNewUser(pDB,pstReqPDU->buf,pstReqPDU->buf+NAME_LEN);
	
	DestroyDictOLPDU(pstReqPDU);
	pstReqPDU = NULL;
	
	pstRspPDU = CreateRegisterRSPPDU(dbret);
	if(NULL == pstRspPDU)
	{
		PrintServerError("Handle Reg Failed Because CreateRegisterRSPPDU\n");
		return -1;
		
	}
	ret = SendPDU(fd,pstRspPDU);
	if(ret < 0)
	{
		PrintServerError("Handle Reg Failed Because SendPDU\n");
		dbret = -1;
	}
	DestroyDictOLPDU(pstRspPDU);
	pstRspPDU = NULL;
	return dbret;
}


/*	
	处理登录请求，无论成功与否，销毁请求PDU
	return 0登录成功， < 0出错，> 0登录失败，但允许用户继续尝试注册或登录
*/
static int HandleLogin(int fd,sqlite3 *pDB,struct DictOLPDU *pstReqPDU)
{
	int checkret = 0;
	int ret = 0;
	struct DictOLPDU *pstRspPDU = NULL;

	checkret = CheckLogin(pDB,pstReqPDU->buf,pstReqPDU->buf+NAME_LEN);

	PrintServerInfo("CheckLogin return value is %d\n",checkret);	
	DestroyDictOLPDU(pstReqPDU);
	pstReqPDU = NULL;
	
	pstRspPDU = CreateLoginRSPPDU(checkret);
	if(NULL == pstRspPDU)
	{
		PrintServerError("Handle Login Failed Because CreateRegisterRSPPDU\n");
		return -1;
		
	}
	ret = SendPDU(fd,pstRspPDU);
	if(ret < 0)
	{
		PrintServerError("Handle Login Failed Because SendPDU\n");
		checkret = -1;
	}
	DestroyDictOLPDU(pstRspPDU);
	pstRspPDU = NULL;
	return checkret;
}

static struct DictOLPDU * QueryWordFromFile(char *word)
{
	FILE *fp = NULL;
	char *pline = NULL;
	char *p = NULL;
	int len;
	int result;
	struct DictOLPDU *pstRspPDU = NULL;

    len = strlen(word);
    if ((fp = fopen("dict.txt", "r")) == NULL)
    {
		PrintServerError("fopen dict.txt failed\n");		
		return NULL;
    }

    printf("query word is %s\n",word);
	pline = MyReadLineFromTxt(fp,NULL);
    while (pline != NULL)
    {
        result = strncmp(word, pline, len);
        if (result > 0) 
		{
			free(pline);
			pline = NULL;
			pline = MyReadLineFromTxt(fp,NULL);
			continue;
		}
        if (result < 0 || pline[len] != ' ') 
		{
			free(pline);
			pline = NULL;
			break;
		}
		else
		{
			break;
		}
    }
    fclose(fp);
	fp = NULL;

	if(pline != NULL)
	{
		p = pline + len;
		while(*p == ' ') 
		{
			p++;
		}
	}
	if(p != NULL)
	{
		pstRspPDU = CreateQueryWordRSPPDU(p);
		free(pline);
		pline = NULL;
		p = NULL;
	}
	else
	{
		pstRspPDU = CreateQueryWordRSPPDU(QUERY_WORD_ERR_STR);
	}

	return pstRspPDU;	
}

/*	
	处理查词请求，无论成功与否，销毁请求PDU
	return 0查词成功， < 0出错，> 0查词失败，但可继续使用下次服务
*/
static int HandleQueryWord(int fd,sqlite3 *pDB,struct DictOLPDU *pstReqPDU,char *username)
{
	int ret = 0;
	struct DictOLPDU *pstRspPDU = NULL;

	pstRspPDU = QueryWordFromFile(pstReqPDU->buf);
	if(NULL == pstRspPDU)
	{
		PrintServerError("Handle QueryWord Failed Because QueryWordFromFile\n");
		DestroyDictOLPDU(pstReqPDU);
		pstReqPDU = NULL;
		return -1;
	}

	ret = SendPDU(fd,pstRspPDU);
	if(ret < 0)
	{
		PrintServerError("Handle QueryWord Failed Because SendPDU\n");
	}
	else
	{
		if(strcmp(pstRspPDU->buf,QUERY_WORD_ERR_STR) != 0)
		{//查到词，插入或更新历史记录
			if(0 != InsertOrUpdateHistoryRecord(pDB,username,pstReqPDU->buf))
			{
				PrintServerError("After QueryWord,InsertOrUpdateHistoryRecord Failed\n");
			}
		}
	}
	DestroyDictOLPDU(pstRspPDU);
	pstRspPDU = NULL;
	DestroyDictOLPDU(pstReqPDU);
	pstReqPDU = NULL;
	return ret;
}

/*	
	处理查史请求，无论成功与否，销毁请求PDU
	return 0查史成功， < 0出错，> 0查史失败，但可继续使用下次服务
*/
static int HandleQueryHistory(int fd,sqlite3 *pDB,struct DictOLPDU *pstReqPDU,char *username)
{
	int ret = 0;
	struct DictOLPDU *pstRspPDU = NULL;
	char *allhistory = NULL;

	DestroyDictOLPDU(pstReqPDU);
	pstReqPDU = NULL;

	allhistory = GetUserAllHistoryRecords(pDB,username);
	if(NULL == allhistory)
	{
		PrintServerError("Handle QueryHistory Failed Because GetUserAllHistoryRecords\n");
		return -1;
	}
	
	pstRspPDU = CreateHistoryRSPPDU(allhistory);
	free(allhistory);
	allhistory = NULL;
	if(NULL == pstRspPDU)
	{
		PrintServerError("Handle QueryHistory Failed Because CreateRegisterRSPPDU\n");
		return -1;
		
	}
	ret = SendPDU(fd,pstRspPDU);
	if(ret < 0)
	{
		PrintServerError("Handle QueryHistory Failed Because SendPDU\n");
	}
	DestroyDictOLPDU(pstRspPDU);
	pstRspPDU = NULL;
	return ret;
}

