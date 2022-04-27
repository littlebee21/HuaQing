#ifndef SERVER_PRIVATE_H
#define SERVER_PRIVATE_H

#include <signal.h>
#include <sqlite3.h>
#include "dictolpublic.h"

int HandleClient(int fd,sqlite3 *pDB);

/*wrap sqlite3 run sql sentence function for read-write lock when multi-processes handle same database*/
int my_sqlite3_exec(sqlite3 *pDB,const char *sqlstr,int (*callback)(void *,int,char **,char **),void *arg,char **errmsg);
int my_sqlite3_get_table(sqlite3 *pDB,const char *sqlstr,char ***pret,int *prows,int *pcols,char **errmsg);


/*open and create table*/
sqlite3 *CreateSQLite3Engine(char *dbfile);

/*operate user table in database*/
int InsertNewUser(sqlite3 *pDB,char *username,char *password);
int CheckLogin(sqlite3 *pDB,char *username,char *password);
int UpdateUserFlag(sqlite3 *pDB,char *username,int flag);

/*operate history table in database*/
int InsertOrUpdateHistoryRecord(sqlite3 *pDB,char *username,char *word);
char *GetUserAllHistoryRecords(sqlite3 *pDB,char *username);

#endif
