#include "sprivate.h"


/*
	0:Insert OK
	1:user is exist
	2:other error
*/
int InsertNewUser(sqlite3 *pDB,char *username,char *password)
{
	char sqlstr[128] = "";
	int ret = 0;
	int rows = 0;
	int cols = 0;
	char * errmsg = NULL;
	char ** ppret = NULL;

	/*check exist*/
	sprintf(sqlstr,"SELECT count(*) FROM user WHERE username = '%s'",username);
	ret = my_sqlite3_get_table(pDB,sqlstr,&ppret,&rows,&cols,&errmsg);
	if(ret != SQLITE_OK)
	{
		PrintServerError("sqlite3_get_table failed:%s\n",errmsg);
		sqlite3_free(errmsg);
		sqlite3_free_table(ppret);
		return 2;
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

	if(ret >= 1)
	{
		return 1;
	}

	/*insert new*/
	memset(sqlstr,0,128);
	sprintf(sqlstr,"INSERT INTO user VALUES('%s','%s',0)",username,password);
	ret = my_sqlite3_exec(pDB,sqlstr,NULL,NULL,&errmsg);
	if(ret != SQLITE_OK)
	{
		PrintServerError("sqlite3_exec failed:%s\n",errmsg);
		sqlite3_free(errmsg);
		return 2;
	}
	
	return 0;
}


/*
	0:find user and password correct and flag is zero(This user is not logining now)
    1:Not find user
    2:flag is not zero(login already)
    3:password is not correct
	4:other error
*/
int CheckLogin(sqlite3 *pDB,char *username,char *password)
{
	char sqlstr[128] = "";
	int ret = 0;
	int rows = 0;
	int cols = 0;
	char * errmsg = NULL;
	char ** ppret = NULL;
	int flag = 0;

	sprintf(sqlstr,"SELECT * FROM user WHERE username = '%s'",username);
	ret = my_sqlite3_get_table(pDB,sqlstr,&ppret,&rows,&cols,&errmsg);
	if(ret != SQLITE_OK)
	{
		PrintServerError("sqlite3_get_table failed:%s\n",errmsg);
		sqlite3_free(errmsg);
		ret = 4;
		goto EXIT;
	}
	if(rows < 1)
    {
		ret = 1;
		goto EXIT;
    }

	sscanf(*((ppret + cols) + 2),"%d",&flag);
	if(flag)
	{
		ret = 2;
		goto EXIT;
	}

	if(strcmp(password,*(ppret + cols + 1)) != 0)
	{
		ret = 3;
		goto EXIT;
	}

	ret = 0;
	UpdateUserFlag(pDB,username,1);
EXIT:	
    sqlite3_free_table(ppret);

	return ret;		
}


int UpdateUserFlag(sqlite3 *pDB,char *username,int flag)
{
	char sqlstr[128] = "";
	int ret = 0;
	char * errmsg = NULL;
	
	if(flag < 0 || flag > 1)
	{
		return 1;
	}

	sprintf(sqlstr,"UPDATE user SET flag = %d WHERE username = '%s'",flag,username);
	ret = my_sqlite3_exec(pDB,sqlstr,NULL,NULL,&errmsg);
	if(ret != SQLITE_OK)
	{
		PrintServerError("sqlite3_exec failed:%s\n",errmsg);
		sqlite3_free(errmsg);
		return 2;
	}

	return 0;
}
