#include <stdio.h>

#include <sqlite3.h>

int my_sqlite3_get_table(sqlite3 *db,const char *zSql,char ***pazResult,int *pnRow,int *pnColumn,char **pzErrmsg);
int my_sqlite3_exec(sqlite3* pdb, const char *sql, sqlite3_callback callback, void*para, char** errmsg);
int insert_new_student(sqlite3 *psql,int id,char *name,char sex,float score)
{
	char *perr = NULL;
	int ret = 0;
	char sqlstr[256] = "";

	sprintf(sqlstr,"INSERT INTO stu VALUES(%d,'%s','%c',%.1f)",id,name,sex,score);

	ret = my_sqlite3_exec(psql,sqlstr,NULL,NULL,&perr);
	if(ret != SQLITE_OK)
	{
		printf("exec %s failed:%s\n",sqlstr,perr);
		sqlite3_free(perr);
		perr = NULL;
		return -1;
	}

	return 0;

}

int delete_student_by_id(sqlite3 *psql,int id)
{
	char *perr = NULL;
	int ret = 0;
	char sqlstr[256] = "";

	sprintf(sqlstr,"DELETE FROM stu WHERE id = %d",id);

	ret = my_sqlite3_exec(psql,sqlstr,NULL,NULL,&perr);
	if(ret != SQLITE_OK)
	{
		printf("exec %s failed:%s\n",sqlstr,perr);
		sqlite3_free(perr);
		perr = NULL;
		return -1;
	}

	return 0;
}
