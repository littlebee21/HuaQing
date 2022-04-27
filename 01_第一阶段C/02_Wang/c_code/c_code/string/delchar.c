#include <stdio.h>

int input_string(char *pstr,int cnt);
char *mygets(char *pout,int size);
char input_char();
int del_char(char *pstr,char c);

#define STR_LEN 40
int main()
{
	char buf[STR_LEN] = "";
	char ch = '\0';

	input_string(buf,STR_LEN);

	ch = input_char();

	del_char(buf,ch);

	printf("buf=%s\n",buf);
	return 0;
}

char input_char()
{
	char x = '\0';

	printf("Please input a char\n");
	x = getchar();

	while(getchar() != '\n')
	{
	}

	return x;
}

int input_string(char *pstr,int cnt)
{
	printf("Please input a string:\n");
	mygets(pstr,cnt);

	return 0;
}

int del_char(char *pstr,char c)
{
	char *p = NULL;
	char *q = NULL;
	int cnt = 0;

	p = q = pstr;

	while(*p != '\0')
	{
		if(*p == c)
		{
			cnt++;		
		}
		else
		{
			*q = *p;
			q++;
		}
		p++;
	}
	*q=*p;//'\0'

	return cnt;
}
