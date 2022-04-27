#include "mysem.h"

union semun
{
        int   val;//SETVAL时指定要设置的值
        struct  semid_ds *buf;//IPC_STAT和IPC_SET时配合获取或设置IPC对象信息
        unsigned short  *array; //GETALL和SETALL时配合获取或设置所有值
        struct seminfo *__buf;  /* buffer for IPC_INFO */
};

int create_a_sem()
{
	key_t key;
	int id = -1;

	key = ftok(KEY_FILE_NAME,6);

	id = semget(key,1,0666 | IPC_CREAT);
	if(id < 0)
	{
		printf("create or open sem-set failed,ret=%d\n",id);
		return -1;
	}

	return id;
}


int set_sem_value(int id,int val)
{
	union semun arg;
	int ret = 0;

	arg.val = val;

	ret = semctl(id,0,SETVAL,arg);
	if(ret < 0)
	{
		printf("set sem init-value failed\n");
		return -1;
	}

	return 0;
}

int my_sem_p(int id,int val)
{
	struct sembuf op;
	int ret = 0;

	if(val < 0)
	{
		printf("val is invalid\n");
		return -1;
	}

	op.sem_num = 0;
	op.sem_op = -val;
	op.sem_flg = SEM_UNDO;

	ret = semop(id,&op,1);
	if(ret < 0)
	{
		printf("semop-p failed\n");
	}

	return ret;
}

int my_sem_v(int id,int val)
{
	struct sembuf op;
	int ret = 0;

	if(val < 0)
	{
		printf("val is invalid\n");
		return -1;
	}

	op.sem_num = 0;
	op.sem_op = val;
	op.sem_flg = SEM_UNDO;

	ret = semop(id,&op,1);
	if(ret < 0)
	{
		printf("semop-v failed\n");
	}

	return ret;
}

