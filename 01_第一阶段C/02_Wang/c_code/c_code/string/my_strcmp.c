#include <stdio.h>

int my_strcmp(char *pstr1,char *pstr2);
int main()
{
	char *p1 = "abc";
	char *p2 = "abc";
	int ret = 0;

	ret = my_strcmp(p1,p2);
	if(ret > 0)
	{
		printf("The max string is %s\n",p1);
	}
	else if(ret < 0)
	{
		printf("The max string is %s\n",p2);
	}
	else
	{
		printf("%s == %s\n",p1,p2);
	}

	return 0;
}

int my_strcmp(char *pstr1,char *pstr2)
{
	int i = 0;

	while(*(pstr1+i) == *(pstr2+i) && *(pstr1+i) != '\0' && *(pstr2+i) != '\0')
	{
		i++;
	}

	return *(pstr1+i) - *(pstr2+i);
}
