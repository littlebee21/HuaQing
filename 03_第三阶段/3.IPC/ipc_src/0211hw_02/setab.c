#include "setab.h"

int main(int argc,char *argv[])
{
	char ch = '\n';
	int i = 0;
	key_t shm_key = 0;
	int shmid = -1;
	char *psh = NULL;
	int semid = -1;

	if(argc < 2)
	{
		printf("The argument is too few\n");
		return 1;
	}

	ch = *(argv[1]);

	shm_key = ftok(SHMEM_KEY_F,SHMEM_KEY_V);

	shmid = shmget(shm_key,SHMEM_LEN,0666 | IPC_CREAT);
	if(shmid < 0)
	{
		printf("shmget failed\n");
		return 2;
	}

	psh = shmat(shmid,NULL,0);
	if(NULL == psh)
	{
		printf("shmat failed\n");
		return 3;
	}

	semid =  create_a_sem();
	set_sem_value(semid,1);

	my_sem_p(semid,1);
	for(i = 0;i < 20;i++)
	{
		*(psh + i) = ch;
		sleep(1);	
	}
	my_sem_v(semid,1);

	shmdt(psh);
	psh = NULL;

	printf("End of set %c\n",ch);
	return 0;
}
