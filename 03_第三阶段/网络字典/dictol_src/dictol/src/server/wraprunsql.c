#include "sprivate.h"

int my_sqlite3_exec(sqlite3 *pDB,const char *sqlstr,int (*callback)(void *,int,char **,char **),void *arg,char **errmsg)
{
	int ret = 0;

	while(1)
	{
		ret = sqlite3_exec(pDB,sqlstr,callback,arg,errmsg);
		if(ret == SQLITE_BUSY || ret == SQLITE_LOCKED)
		{
			usleep(30 * 1000);
			continue;
		}
		else
		{
			break;
		}
	}

	return ret;
}


int my_sqlite3_get_table(sqlite3 *pDB,const char *sqlstr,char ***pret,int *prows,int *pcols,char **errmsg)
{
	int ret = 0;

	while(1)
	{
		ret = sqlite3_get_table(pDB,sqlstr,pret,prows,pcols,errmsg);
		if(ret == SQLITE_BUSY || ret == SQLITE_LOCKED)
		{
			usleep(30 * 1000);
			continue;
		}
		else
		{
			break;
		}
	}

	return ret;
}


sqlite3 *CreateSQLite3Engine(char *dbfile)
{
	sqlite3 *pdb = NULL;
	int ret = 0;
	int has_table = 0;
	char sqlstr[128] = "";
	int rows = 0;
	int cols = 0;
	char *errstr = NULL;
	char **ppret = NULL;

	//打开数据库，如果不存在则创建并打开	
	ret = sqlite3_open(dbfile,&pdb);
	if(ret != SQLITE_OK)
	{
		PrintServerError("open sqlite failed:%s\n",sqlite3_errmsg(pdb));
		sqlite3_close(pdb);
		return NULL;
	}

    //检查user表是否存在，不存在则创建
	sprintf(sqlstr,"SELECT count(*) FROM sqlite_master WHERE type = 'table' AND name = 'user'");
    ret = sqlite3_get_table(pdb,sqlstr,&ppret,&rows,&cols,&errstr);
    if(ret != SQLITE_OK)
    {
    	PrintServerError("sqlite3_get_table failed:%s\n",errstr);
        sqlite3_free(errstr);
        sqlite3_free_table(ppret);
        sqlite3_close(pdb);
        return NULL;
    }
	if(rows < 1)
	{
		has_table = 0;
	}
	else
	{
       	sscanf(ppret[1],"%d",&has_table);
	}
	sqlite3_free_table(ppret);

	if(has_table == 0)
	{
		sprintf(sqlstr,"CREATE TABLE user(username TEXT(%d) PRIMARY KEY NOT NULL,password TEXT(%d),flag INT)",
               NAME_LEN,PASS_LEN);
        ret = sqlite3_exec(pdb,sqlstr,NULL,NULL,&errstr);
        if(ret != SQLITE_OK)
        {
        	PrintServerError("sqlite3_exec failed:%s\n",errstr);
            sqlite3_free(errstr);
            sqlite3_close(pdb);
            return NULL;
		}
	}

    //检查history表是否存在，不存在则创建
	sprintf(sqlstr,"SELECT count(*) FROM sqlite_master WHERE type = 'table' AND name = 'history'");
    ret = sqlite3_get_table(pdb,sqlstr,&ppret,&rows,&cols,&errstr);
    if(ret != SQLITE_OK)
    {
    	PrintServerError("sqlite3_get_table failed:%s\n",errstr);
        sqlite3_free(errstr);
        sqlite3_free_table(ppret);
        sqlite3_close(pdb);
        return NULL;
    }
	if(rows < 1)
	{
		has_table = 0;
	}
	else
	{
        	sscanf(ppret[1],"%d",&has_table);
	}
	sqlite3_free_table(ppret);

	if(has_table == 0)
	{
		sprintf(sqlstr,"CREATE TABLE history(id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                               "username TEXT(%d),time TEXT(24),word TEXT(%d))",NAME_LEN,WORD_LEN);
        ret = sqlite3_exec(pdb,sqlstr,NULL,NULL,&errstr);
        if(ret != SQLITE_OK)
        {
        	PrintServerError("sqlite3_exec failed:%s\n",errstr);
            sqlite3_free(errstr);
            sqlite3_close(pdb);
            return NULL;
		}
	}
	return pdb;
}
