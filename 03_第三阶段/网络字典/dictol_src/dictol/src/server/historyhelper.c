#include "sprivate.h"

static int CheckRecordIsExist(sqlite3 *pDB,char *username,char *word)
{
	char sqlstr[128] = "";
	int ret = 0;
	int rows = 0;
	int cols = 0;
	char * errmsg = NULL;
	char ** ppret = NULL;
	
	sprintf(sqlstr,"SELECT count(*) FROM history WHERE username = '%s' and word = '%s'",username,word);
	ret = my_sqlite3_get_table(pDB,sqlstr,&ppret,&rows,&cols,&errmsg);
	if(ret != SQLITE_OK)
	{
		PrintServerError("sqlite3_get_table failed:%s\n",errmsg);
		sqlite3_free(errmsg);
		sqlite3_free_table(ppret);
		return -1;
	}
	if(rows < 1)
    {
	    ret = 0;
    }
    else
    {
    	sscanf(ppret[1],"%d",&ret);
    }
    sqlite3_free_table(ppret);

	return ret;
}

static int InsertNewHistoryRecord(sqlite3 *pDB,char *username,char *word)
{
	char sqlstr[128] = "";
	int ret = 0;
	char * errmsg = NULL;
	
	sprintf(sqlstr,"INSERT INTO history(username,time,word) VALUES('%s',datetime('now','localtime'),'%s')",username,word);
	ret = my_sqlite3_exec(pDB,sqlstr,NULL,NULL,&errmsg);
	if(ret != SQLITE_OK)
	{
		PrintServerError("sqlite3_exec failed:%s\n",errmsg);
		sqlite3_free(errmsg);
		return -1;
	}

	return 0;
}

static int UpdateHistoryRecordTime(sqlite3 *pDB,char *username,char *word)
{
	char sqlstr[128] = "";
	int ret = 0;
	char * errmsg = NULL;
	
	sprintf(sqlstr,"UPDATE history SET time = datetime('now','localtime') WHERE username = '%s' AND word = '%s'",username,word);
	ret = my_sqlite3_exec(pDB,sqlstr,NULL,NULL,&errmsg);
	if(ret != SQLITE_OK)
	{
		PrintServerError("sqlite3_exec failed:%s\n",errmsg);
		sqlite3_free(errmsg);
		return -1;
	}

	return 0;
	
}

int InsertOrUpdateHistoryRecord(sqlite3 *pDB,char *username,char *word)
{
	int ret = 0;
	
	ret = CheckRecordIsExist(pDB,username,word);
	if(ret == 0)
	{//记录不存在
		ret = InsertNewHistoryRecord(pDB,username,word);
	}
	else if(ret > 0)
	{//记录已存在
		ret = UpdateHistoryRecordTime(pDB,username,word);
	}
	
	return ret;
}

/*返回空间为动态分配，一旦不再使用此空间，应及时free*/
char *GetUserAllHistoryRecords(sqlite3 *pDB,char *username)
{
	char sqlstr[128] = "";
	int ret = 0;
	int rows = 0;
	int cols = 0;
	char * errmsg = NULL;
	char ** ppret = NULL;
	int len = 0;
	char *pret = NULL;
	
	sprintf(sqlstr,"SELECT time,word FROM history WHERE username = '%s'",username);
	ret = my_sqlite3_get_table(pDB,sqlstr,&ppret,&rows,&cols,&errmsg);
	if(ret != SQLITE_OK)
	{
		PrintServerError("sqlite3_get_table failed:%s\n",errmsg);
		sqlite3_free(errmsg);
		sqlite3_free_table(ppret);
		return NULL;
	}
	if(rows < 1)
    {
      	sqlite3_free_table(ppret);
		len = strlen(QUERY_HISTORY_ERR_STR) + 1;
		pret = (char *)malloc(len);
		if(NULL == pret)
		{
			PrintServerError("malloc failed!\n");
			return NULL;
		}
		memset(pret,0,len);
		strcpy(pret,QUERY_HISTORY_ERR_STR);
        return pret;
    }
    else
    {
		char **pptmp = NULL;
		int i = 0;

		pptmp = ppret + cols;//跳过表头字符串
		len = 0;
		/*count len*/
		for(i = 0;i < rows * cols;i++)
		{
			len += strlen(*(pptmp+i));
			len++;//间隔符 #分隔时间和单词 @分隔记录
		}
		len++;//结束符 '\0'
		
		/*malloc memory*/
		pret = (char *)malloc(len);
		if(NULL == pret)
		{
			PrintServerError("malloc failed!\n");
      		sqlite3_free_table(ppret);
			return NULL;
		}
		memset(pret,0,len);
		
		for(i = 0;i < rows;i++)
		{
			strcat(pret,*(pptmp + i * cols));
			strcat(pret,"#");
			strcat(pret,*(pptmp + i * cols + 1));
			strcat(pret,"@");
		}	
       	sqlite3_free_table(ppret);
    }

	return pret;
}


