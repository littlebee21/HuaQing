#include <stdio.h>

int my_strcpy1(char inbuf[],char outbuf[]);
char * my_strcpy2(char *pdest,char *psrc);
char * my_strncpy(char *pdest,char *psrc,int n);
int main()
{
	char str1[] = "ahsdfhgsadh";
	char str2[20] = "";


	my_strncpy(str2,str1,15);

	printf("The str2 is %s\n",str2);
	return 0;
}

int my_strcpy1(char inbuf[],char outbuf[])
{
	int i = 0;

	while(inbuf[i] != '\0')
	{
		outbuf[i] = inbuf[i];
		i++;
	}
	outbuf[i] = inbuf[i];//copy '\0'

	return i+1;
}

char * my_strcpy2(char *pdest,char *psrc)
{
	char *p = psrc;
	char *q = pdest;

	while(*p != '\0')
	{
		*q = *p;
		p++;
		q++;
	}
	*q = *p;
	return pdest;
}

char * my_strncpy(char *pdest,char *psrc,int n)
{
	char *p = psrc;
	char *q = pdest;
	int cnt = 0;

	while(*p != '\0')
	{
		if(cnt >= n)
		{
			break;
		}
		*q = *p;
		p++;
		q++;
		cnt++;
	}

	while(cnt < n)
	{
		*q = '\0';
		q++;
		cnt++;
	}

	return pdest;
}
