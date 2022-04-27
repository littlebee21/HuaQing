#include <stdio.h>

int main(int argc,char *argv[])
{
	FILE *pf = NULL;
	int loc = 0;

	if(argc < 2)
	{
		printf("The argument is too few,Usage:./getfilesize ???\n");
		return 1;
	}

	/*r-mode*/
	pf = fopen(argv[1],"r");
	if(NULL == pf)
	{
		printf("fopen %s failed\n",argv[1]);
		return 1;
	}

	fseek(pf,0,SEEK_END);
	loc = ftell(pf);
	printf("The file size of %s is %d\n",argv[1],loc);
		
	fclose(pf);
	pf = NULL;
	
	return 0;
}
