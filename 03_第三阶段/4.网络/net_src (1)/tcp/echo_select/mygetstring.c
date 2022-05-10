#include <stdio.h>
#include <string.h>


char *mygetstring(char *buf,int size)
{
	int len = 0;

	fgets(buf,size,stdin);
	len = strlen(buf);
	if(buf[len-1] == '\n')
	{
		buf[len-1] = '\0';
	}
	else
	{
		while(getchar() != '\n')
		{
		}
	}
	return buf;
}
