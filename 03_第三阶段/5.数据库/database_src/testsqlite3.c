#include <stdio.h>

#include <sqlite3.h>

#define DB_FILE "./test.db"

int print_one_line(void* para,int columnCount,  char** columnValue,char** columnName);

int main(int argc,char *argv[])
{
	sqlite3 *psqlengine = NULL;
	int ret = 0;
	char sqlstr[80] = "";
	char *perrmsg = NULL;

	ret = sqlite3_open(DB_FILE,&psqlengine);
	if(ret != SQLITE_OK)
	{
		printf("sqlite3_open failed:%s\n",sqlite3_errmsg(psqlengine));
		sqlite3_close(psqlengine);
		psqlengine = NULL;
		return 1;
	}

	sprintf(sqlstr,"%s","SELECT * FROM student");
	ret = sqlite3_exec(psqlengine,sqlstr,print_one_line,NULL,&perrmsg);
	if(ret != SQLITE_OK)
	{
		printf("exec %s failed:%s\n",sqlstr,perrmsg);
		sqlite3_free(perrmsg);
		perrmsg = NULL;
	}

	{
		int rows = 0;
		int cols = 0;
		char **ppret = NULL;

		sprintf(sqlstr,"%s","SELECT * FROM student");
		ret = sqlite3_get_table(psqlengine,sqlstr,&ppret,&rows,&cols,&perrmsg);
		if(ret != SQLITE_OK)
		{
			printf("exec %s failed:%s\n",sqlstr,perrmsg);
			sqlite3_free(perrmsg);
			perrmsg = NULL;
		}
		else
		{
			int i = 0;
			int j = 0;

			printf("rows=%d,cols=%d\n",rows,cols);
			
			/*打印每个字段的名字*/
			for(j = 0;j < cols;j++)
			{
				printf("%-12s",*(ppret+j));
			}
			printf("\n");

			/*打印每行每个字段值*/
			for(i = 1;i <= rows;i++)
			{
				for(j = 0;j < cols;j++)
				{
					printf("%-12s",*(ppret + i * cols + j));
				}
				printf("\n");
			}

			sqlite3_free_table(ppret);
			ppret = NULL;
		}
	}

	sqlite3_close(psqlengine);
	psqlengine = NULL;
	return 0;
}

int print_one_line(void* para,int columnCount,  char** columnValue,char** columnName)
{
	int i = 0;
	static int printhead = 0;
	
	if(0 == printhead)
	{
		for(i = 0;i < columnCount;i++)
		{
			printf("%-20s ",*(columnName+i));
		}
		printf("\n");
		printhead = 1;
	}

	for(i = 0;i < columnCount;i++)
	{
		printf("%-20s ",*(columnValue+i));
	}
	printf("\n");

	return 0;
}
