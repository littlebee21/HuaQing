#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sprivate.h"

sqlite3 *CreateSQLite3Engine(char *dbfile);

int InsertNewUser(sqlite3 *pDB,char *username,char *password);
int CheckLogin(sqlite3 *pDB,char *username,char *password);
int UpdateUserFlag(sqlite3 *pDB,char *username,int flag);

int InsertOrUpdateHistoryRecord(sqlite3 *pDB,char *username,char *word);
char *GetUserAllHistoryRecords(sqlite3 *pDB,char *username);

int main()
{
	sqlite3 *pdb = NULL;
	int ret = 0;
	char *phis = NULL;

	pdb = CreateSQLite3Engine("./ttt.db");

/*test user table*/
	ret = InsertNewUser(pdb,"abc","abc");
	printf("In %s at %d,ret = %d\n",__FILE__,__LINE__,ret);

	ret = InsertNewUser(pdb,"def","def");
	printf("In %s at %d,ret = %d\n",__FILE__,__LINE__,ret);
	
	ret = InsertNewUser(pdb,"xyz","xyz");
	printf("In %s at %d,ret = %d\n",__FILE__,__LINE__,ret);

	ret = InsertNewUser(pdb,"xyz","hhh");
	printf("In %s at %d,ret = %d\n",__FILE__,__LINE__,ret);
	
	ret = UpdateUserFlag(pdb,"def",1);
	printf("In %s at %d,ret = %d\n",__FILE__,__LINE__,ret);

	ret = CheckLogin(pdb,"qqq","123");
	printf("In %s at %d,ret = %d\n",__FILE__,__LINE__,ret);

	ret = CheckLogin(pdb,"def","def");
	printf("In %s at %d,ret = %d\n",__FILE__,__LINE__,ret);
	
	ret = CheckLogin(pdb,"xyz","iiii");
	printf("In %s at %d,ret = %d\n",__FILE__,__LINE__,ret);
	
	ret = CheckLogin(pdb,"abc","abc");
	printf("In %s at %d,ret = %d\n",__FILE__,__LINE__,ret);

/*test history table*/

	ret = InsertOrUpdateHistoryRecord(pdb,"abc","hello");
	printf("In %s at %d,ret = %d\n",__FILE__,__LINE__,ret);
	
	ret = InsertOrUpdateHistoryRecord(pdb,"abc","bee");
	printf("In %s at %d,ret = %d\n",__FILE__,__LINE__,ret);
	
	ret = InsertOrUpdateHistoryRecord(pdb,"abc","orange");
	printf("In %s at %d,ret = %d\n",__FILE__,__LINE__,ret);
	
	ret = InsertOrUpdateHistoryRecord(pdb,"abc","person");
	printf("In %s at %d,ret = %d\n",__FILE__,__LINE__,ret);

	sleep(3);	
	ret = InsertOrUpdateHistoryRecord(pdb,"abc","person");
	printf("In %s at %d,ret = %d\n",__FILE__,__LINE__,ret);

	phis = GetUserAllHistoryRecords(pdb,"abc");
	if(phis != NULL)
	{
		printf("history is %s\n",phis);
		free(phis);
	}
	else
	{
		printf("In %s at %d,no history\n",__FILE__,__LINE__);
	}
		
	phis = GetUserAllHistoryRecords(pdb,"xyz");
	if(phis != NULL)
	{
		printf("history is %s\n",phis);
		free(phis);
	}
	else
	{
		printf("In %s at %d,no history\n",__FILE__,__LINE__);
	}
	return 0;	
}
