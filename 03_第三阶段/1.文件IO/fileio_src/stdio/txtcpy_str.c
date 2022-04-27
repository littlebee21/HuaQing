#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *myreadline(FILE *pf);
int main(int argc,char *argv[])
{
	FILE *pfsrc = NULL;
	FILE *pfdest = NULL;
	char *pret = 0;
	int wret = 0;

	if(argc < 3)
	{
		printf("The argumnet is too few,Usage:./txtcpy file1 file2\n");
		return 1;
	}
	pfsrc = fopen(argv[1],"r");
	if(NULL == pfsrc)
	{
		printf("r-fopen %s failed\n",argv[1]);
		return 2;
	}

	pfdest = fopen(argv[2],"w");
	if(NULL == pfsrc)
	{
		printf("w-fopen %s failed\n",argv[2]);
		return 2;
	}


	pret = myreadline(pfsrc);
	while(pret != NULL)
	{
		wret = fputs(pret,pfdest);
		free(pret);
		pret = NULL;
		if(wret < 0)
		{
			printf("%s fputs to %s failed,ret = %d\n",pret,argv[2],wret);
			break;
		}
		pret = myreadline(pfsrc);
	}

	fclose(pfsrc);
	pfsrc=NULL;
	fclose(pfdest);
	pfdest=NULL;
	return 0;
}


