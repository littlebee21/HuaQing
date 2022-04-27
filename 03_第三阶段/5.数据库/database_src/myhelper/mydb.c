#include <unistd.h>
#include <stdio.h>
#include <sqlite3.h>

int my_sqlite3_get_table(sqlite3 *db,const char *zSql,char ***pazResult,int *pnRow,int *pnColumn,char **pzErrmsg);
int my_sqlite3_exec(sqlite3* pdb, const char *sql, sqlite3_callback callback, void*para, char** errmsg);
sqlite3 *create_my_db(const char *mydbfile)
{
	sqlite3 *psql = NULL;
	int ret = 0;
	char sqlstr[256] = "";

	int rows = 0;
	int cols = 0;
	char **ppret = NULL;
	char *perr = NULL;

	int flag = 0;

	ret = sqlite3_open(mydbfile,&psql);
	if(ret != SQLITE_OK)
	{
		printf("sqlite3_open %s failed:%s\n",mydbfile,sqlite3_errmsg(psql));
		sqlite3_close(psql);
		psql = NULL;
		return NULL;
	}

	/*检查相应的表是否存在，不存在则建表*/
	sprintf(sqlstr,"SELECT count(*)  FROM sqlite_master WHERE type='table' AND name = '%s'","stu");
	ret = my_sqlite3_get_table(psql,sqlstr,&ppret,&rows,&cols,&perr);
	if(ret != SQLITE_OK)
	{
		printf("sqlite3_get_table %s failed:%s\n",sqlstr,perr);
		sqlite3_free(perr);
		perr = NULL;
		sqlite3_close(psql);
		psql = NULL;
		return NULL;
	}
	sscanf(*(ppret + cols),"%d",&flag);
	sqlite3_free_table(ppret);
	ppret = NULL;
	printf("flag=%d\n",flag);
	if(0 == flag)
	{//建表
		sprintf(sqlstr,"CREATE TABLE stu(id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,name TEXT,sex TEXT(1),score REAL)");
		ret = my_sqlite3_exec(psql,sqlstr,NULL,NULL,&perr);
		if(ret != SQLITE_OK)
		{
			printf("sqlite3_exec %s failed:%s\n",sqlstr,perr);
			sqlite3_free(perr);
			perr = NULL;
			sqlite3_close(psql);
			psql = NULL;
			return NULL;
		}
	}


	return psql;
}

int destroy_my_db(sqlite3 *psql)
{
	if(psql != NULL)
	{
		sqlite3_close(psql);
		psql = NULL;
	}

	return 0;
}


int my_sqlite3_exec(sqlite3* pdb, const char *sql, sqlite3_callback callback, void*para, char** errmsg)
{
	int ret = 0;

	do
	{
		ret = sqlite3_exec( pdb , sql, callback , para , errmsg );

    	if (ret == SQLITE_BUSY || ret == SQLITE_LOCKED)
    	{
			usleep(30 * 1000);
        	continue;
    	}
    	else
    	{
        	break;
    	}
	} while(1);

    return ret;
}

int my_sqlite3_get_table(sqlite3 *db,const char *zSql,char ***pazResult,int *pnRow,int *pnColumn,char **pzErrmsg)
{
	int ret = 0;

	do
	{
		ret = sqlite3_get_table(db,zSql,pazResult,pnRow,pnColumn,pzErrmsg);

    	if (ret == SQLITE_BUSY || ret == SQLITE_LOCKED)
    	{
			usleep(30 * 1000);
        	continue;
    	}
    	else
    	{
        	break;
    	}
	} while(1);

    return ret;
}
