#include <sys/ipc.h>
#include <sys/shm.h>

#include <stdio.h>

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

	pshare = (char *)shmat(shmid,NULL,SHM_RDONLY);
	if(NULL == pshare)
	{
		printf("shmat failed\n");
		return 2;
	}

	printf("in read-process,share-mem is %s\n",pshare);


	shmdt(pshare);
	pshare = NULL;

	shmctl(shmid,IPC_RMID,NULL);	

	return 0;
}
