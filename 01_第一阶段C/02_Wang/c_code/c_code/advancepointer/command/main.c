#include <stdio.h>
#include <string.h>

struct mycmd
{
	char *cmd;
	void (*pfdoing)(char *);
};

void f1(char *pstr);
void f2(char *pstr);
void f3(char *pstr);
void f4(char *pstr);
void f5(char *pstr);
void f6(char *pstr);
char *mygets(char *pout,int size);

int input_command(char *cmdstr,int cnt);
int run_command(struct mycmd *pcmdarr,int cnt,char *pstr);
#define N 6

int main(int argc,char *argv[])
{
	struct mycmd arr[N] = {
					{"Eat",f1},
					{"Sleep",f2},
					{"PlayGame",f3},
					{"LookBook",f4},
					{"Movie",f5},
					{"Study",f6}
			      };
	char bufcmd[20] = "";

	input_command(bufcmd,20);

	run_command(arr,N,bufcmd);
	return 0;
}

int run_command(struct mycmd *pcmdarr,int cnt,char *pstr)
{
	int ret = 0;
	struct mycmd *pst = NULL;

	for(pst = pcmdarr;pst < pcmdarr + cnt;pst++)
	{
		if(strcmp(pstr,pst->cmd) == 0)
		{
			pst->pfdoing(pst->cmd);
			break;
		}
	}

	if(pst == pcmdarr + cnt)
	{
		ret = -1;
		printf("The command is not supported\n");
	}
	
	return ret;
}


int input_command(char *cmdstr,int cnt)
{
	printf("Please input a command:\n");
	mygets(cmdstr,cnt);

	return 0;
}


void f1(char *pstr)
{
	printf("Call f1:%s\n",pstr);
}
void f2(char *pstr)
{
	printf("Call f2:%s\n",pstr);
}
void f3(char *pstr)
{
	printf("Call f3:%s\n",pstr);
}
void f4(char *pstr)
{
	printf("Call f4:%s\n",pstr);
}
void f5(char *pstr)
{
	printf("Call f5:%s\n",pstr);
}
void f6(char *pstr)
{
	printf("Call f6:%s\n",pstr);
}
