#include <stdio.h>
#include <sqlite3.h>

sqlite3 *create_my_db(const char *mydbfile);
int destroy_my_db(sqlite3 *psql);

int delete_student_by_id(sqlite3 *psql,int id);
int insert_new_student(sqlite3 *psql,int id,char *name,char sex,float score);
int main(int argc,char *argv[])
{
	sqlite3 *psql = create_my_db("./my.db");
	
	insert_new_student(psql,1,"zhangsan",'M',99.5);
	insert_new_student(psql,2,"lisi",'F',93.5);
	insert_new_student(psql,3,"wanger",'M',95.5);
	

	delete_student_by_id(psql,3);

	destroy_my_db(psql);
	psql = NULL;
	return 0;
}
