#include <stdio.h>
#include <string.h>

char *mygets(char *pout,int size);
#define COUTRY_NAME_LEN 20
int main()
{
	char coutry[COUTRY_NAME_LEN] = "";

	printf("Please input your country name:\n");
	mygets(coutry,COUTRY_NAME_LEN);

	if(strcasecmp(coutry,"China") != 0) //比较字符串内容
	//if(coutry != "China")//比较两个地址值，不符合本题
	{
		printf("We come from different country\n");
	}
	else
	{
		printf("We are from China\n");
	}
	return 0;
}
