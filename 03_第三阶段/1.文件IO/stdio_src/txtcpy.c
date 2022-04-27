#include <stdio.h>

int main(int argc,char *argv[])
{
	FILE *pfsrc = NULL;
	FILE *pfdest = NULL;
	int ret = 0;
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


	ret = fgetc(pfsrc);
	while(ret >= 0)
	{
		wret = fputc(ret,pfdest);
		if(wret < 0)
		{
			printf("%d fputc to %s failed\n",ret,argv[2]);
			break;
		}
		ret = fgetc(pfsrc);
	}

	fclose(pfsrc);
	pfsrc=NULL;
	fclose(pfdest);
	pfdest=NULL;
	return 0;
}
