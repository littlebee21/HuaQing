#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Don't forget free return memory*/
char *myreadline(FILE *pf)
{
	int linecnt = 0;
	int oldloc = 0;
	int ret = 0;
	char *pout = NULL;
	char *pret = NULL;

	/*1. 获取指示器指示的字符位置所在行的总字符数----linecnt*/
		/*保存位置指示器的当前指示位置- ftell*/
	oldloc = ftell(pf);

		/*循环读取单个字符直到文件尾或行尾，每读一个字符linecnt++*/
	ret = fgetc(pf);
	while(ret >= 0 && ret != '\n')
	{
		linecnt++;
		ret = fgetc(pf);
	}
	if(ret == '\n')
	{
		linecnt++;//'\n'
	}

		/*恢复位置指示器指示的原位置--fseek*/
	fseek(pf,oldloc,SEEK_SET);

	/*2. 分配linecnt+1字节的内存空间*/

	if(linecnt <= 0)	
	{
		return NULL;
	}

	linecnt++;//'\0'

	pout = (char *)malloc(linecnt);
	if(NULL == pout)
	{
		printf("Malloc failed ! %s:%d\n",__FILE__,__LINE__);
		return NULL;
	}
	memset(pout,0,linecnt);


	/*3. 读出整行*/
	pret = fgets(pout,linecnt,pf);
	if(NULL == pret)
	{
		free(pout);
		pout = NULL;
		printf("read a line failed! %s:%d\n",__FILE__,__LINE__);
		return NULL;
	}

	/*4. 返回动态空间的首地址*/
	return pout;
}

char *mygets_file(char *pout,int cnt,FILE *pf)
{
	int len = 0;
	char *pret = NULL;

	pret = fgets(pout,cnt,pf);
	if(NULL == pret)
	{
		return NULL;
	}

	len = strlen(pout);
	if(*(pout + len - 1) == '\n')
	{
		*(pout + len - 1) = '\0';
	}

	return pout;
}
