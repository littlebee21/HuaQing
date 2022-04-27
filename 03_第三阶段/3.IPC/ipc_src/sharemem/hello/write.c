#include <sys/ipc.h>
#include <sys/shm.h>

#include <stdio.h>
#include <string.h>

int main(int argc,char *argv[])
{
	int shmid = -1;
	key_t shmkey;
	char *pshare = NULL;

	shmkey = ftok("./send.c",1);

	shmid = shmget(shmkey,20,IPC_CREAT | 0666);
	if(shmid < 0)
	{
		printf("shmget failed\n");
		return 1;
	}

	pshare = (char *)shmat(shmid,NULL,0);
	if(NULL == pshare)
	{
		printf("shmat failed\n");
		return 2;
	}

	strcpy(pshare,"hello");


	shmdt(pshare);
	pshare = NULL;
	

	return 0;
}
