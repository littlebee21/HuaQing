#include <stdio.h>

#define FILE_NAME1 "./test.txt"
#define FILE_NAME2 "./xyz.txt"
#define FILE_NAME3 "./abc.txt"
int main(int argc,char *argv[])
{
	FILE *pf = NULL;
	int loc = 0;

	/*r-mode*/
	pf = fopen(FILE_NAME1,"r");
	if(NULL == pf)
	{
		printf("fopen %s failed\n",FILE_NAME1);
		return 1;
	}

	loc = ftell(pf);
	printf("r-mode start loc=%d\n",loc);

	fclose(pf);
	pf = NULL;
	
	/*w-mode*/
	pf = fopen(FILE_NAME2,"w");
	if(NULL == pf)
	{
		printf("fopen %s failed\n",FILE_NAME2);
		return 1;
	}

	loc = ftell(pf);
	printf("w-mode start loc=%d\n",loc);

	fclose(pf);
	pf = NULL;
	
	/*a-mode*/
	pf = fopen(FILE_NAME3,"a");
	if(NULL == pf)
	{
		printf("fopen %s failed\n",FILE_NAME3);
		return 1;
	}

	loc = ftell(pf);
	printf("a-mode start loc=%d\n",loc);

	fclose(pf);
	pf = NULL;
	return 0;
}
