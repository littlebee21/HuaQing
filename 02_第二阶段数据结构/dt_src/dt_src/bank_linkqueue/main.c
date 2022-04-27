#include "intqueue.h"

int input_operater();

int main(int argc,char *argv[])
{
	int cmd = -1;
	int exitflag=0;
	int startno = 1;
	struct intnode *pnew = NULL;
	struct intnode *ptemp = NULL;
	struct bankqueue *pq = create_bankqueue();

	while(1)
	{
		cmd = input_operater();
		switch(cmd)
		{
			case 1://enqueue
				pnew = create_intnode(startno);
				startno++;
				intnode_enqueue(pq,pnew);
				printf("%d is enqueue\n",pnew->no);
				break;
			case 2://dequeue
				ptemp = intnode_dequeue(pq);
				printf("%d custom dequeue\n",ptemp->no);
				destroy_intnode(ptemp);
				ptemp = NULL;
				break;
			case 3://query
				printf("There are %d custom in queue\n",get_bankqueue_len(pq));
				break;
			case 0://exit
				exitflag=1;
				break;
			default:
				break;
		}
		if(exitflag)
		{
			break;
		}
	}

	destroy_bankqueue(pq);
	pq = NULL;
	return 0;
}

int input_operater()
{
	int op = -1;

	printf("Please input your select:\n");
	printf("1.Custom Enqueue\n");
	printf("2.Custom Dequeue\n");
	printf("3.Query the number of custom in queue\n");
	printf("0.Exit the program\n");

	scanf("%d",&op);
	while(getchar() != '\n')
	{
	}

	return op;
}
