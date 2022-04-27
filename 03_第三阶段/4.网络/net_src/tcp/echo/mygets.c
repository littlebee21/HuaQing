#include <stdio.h>
#include <string.h>

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
