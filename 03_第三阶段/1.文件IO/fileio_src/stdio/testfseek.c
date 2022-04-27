#include <stdio.h>

#define FILE_NAME1 "./test.txt"
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

	/*将指示器指示到2号字节位置*/
	//fseek(pf,2,SEEK_SET);
	
	//指示器当前指示位置为0号字节
	fseek(pf,2,SEEK_CUR);

	loc = ftell(pf);
	printf("After seek(2,SEEK_SET) loc=%d\n",loc);

	/*将指示器指示到倒数2号字节位置*/
	fseek(pf,-2,SEEK_END);
	loc = ftell(pf);
	printf("After seek(-2,SEEK_END) loc=%d\n",loc);
		
	fclose(pf);
	pf = NULL;
	
	return 0;
}
