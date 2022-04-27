#include "setab.h"

int main(int argc,char *argv[])
{
	int i = 0;
	key_t shm_key = 0;
	int shmid = -1;
	char *psh = NULL;

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

	printf("content is:\n");
	for(i = 0;i < 20;i++)
	{
		putchar(*(psh + i));
	}
	printf("\n");


	shmdt(psh);
	psh = NULL;
	return 0;
}
