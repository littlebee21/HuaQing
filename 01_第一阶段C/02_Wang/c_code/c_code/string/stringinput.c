#include <stdio.h>
#include <string.h>

char *mygets(char *pout,int size);
int main()
{
	char buf[20] = "";

	printf("Please input a string:\n");
	//scanf("%s",buf);
	//gets(buf)
	mygets(buf,20);

	printf("buf=%s\n",buf);
	return 0;
}

char *mygets(char *pout,int size)
{
	char *p = NULL;

	fgets(pout,size,stdin);

	p = pout + strlen(pout) - 1;

	if(*p == '\n')
	{
		*p = '\0';
	}
	else
	{
		while(getchar() != '\n')
		{
		}
	}

	return pout;
}
