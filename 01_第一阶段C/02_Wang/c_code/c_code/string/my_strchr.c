#include <stdio.h>

char input_char();
int my_strchr1(char buf[],char c);
char * my_strchr2(char *pstr,int c);
int main()
{
	char str[] = "asgdfgahsfha";
	char ch = input_char();
	char *pret = my_strchr2(str,ch);
	
	if(pret == NULL)
	{
		printf("%c is not in %s\n",ch,str);
	}
	else
	{
		printf("%c is in %s at %ld\n",ch,str,pret - str);
	}

	return 0;
}

int my_strchr1(char buf[],char c)
{
	int i = 0;

	while(buf[i] != '\0')
	{
		if(c == buf[i])
		{
			break;
		}

		i++;
	}
	if(buf[i] == '\0')
	{
		return -1;
	}
	else
	{
		return i;
	}
}

char * my_strchr2(char *pstr,int c)
{
	char *p= pstr;
	
	while(*p != '\0')
	{
		if(*p == c)
		{
			break;
		}
		p++;
	}

	if(*p == '\0')
	{
		return NULL;
	}
	else
	{
		return p;
	}
}

char input_char()
{
	char x = '\0';

	printf("Please input a char:\n");
	x = getchar();

	while(getchar() != '\n')
	{
	}

	return x;
}
