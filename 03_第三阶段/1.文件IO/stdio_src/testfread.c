#include <stdio.h>

#define FILE_NAME "./kkk.txt"

int main(int argc,char *argv[])
{
	FILE *pf = NULL;
	char buf1[6] = "";
	char buf2[8] = "";

	pf = fopen(FILE_NAME,"r");
	if(NULL == pf)
	{
		printf("Fopen %s failed\n",FILE_NAME);
		return 1;
	}

	fseek(pf,9,SEEK_SET);//指示器指示位置 ---- 9号字节
	fread(buf1,sizeof(char),4,pf);//指示器指示位置 ---- 13号字节
	fread(buf2,sizeof(char),6,pf);

	printf("buf1=%s\n",buf1);
	printf("buf2=%s\n",buf2);


	fclose(pf);
	pf = NULL;
	return 0;
}
