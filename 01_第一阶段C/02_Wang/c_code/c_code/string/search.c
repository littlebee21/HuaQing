#include <stdio.h>
#include <string.h>


char *mygets(char *pout,int size);
int input_string(char *pout,int cnt);
char input_char();

#define STR1_LEN 40
#define STR2_LEN 16
int main()
{
	char str1[STR1_LEN] = "";
	char str2[STR2_LEN] = "";
	char ch = '\0';
	char *pret = NULL;
	char *pc = NULL;

	input_string(str1,STR1_LEN);
	input_string(str2,STR2_LEN);
	ch = input_char();

	pret = strstr(str1,str2);
	if(NULL == pret)
	{
		printf("%s is not in %s\n",str2,str1);
		return 1;
	}
	else
	{
		pc = strchr(pret,ch);
		if(NULL == pc)
		{
			printf("Not find %c\n",ch);
		}
		else
		{
			printf("Address of %c is %p\n",ch,pc);
		}
	}


	return 0;
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

int input_string(char *pout,int cnt)
{
	printf("Please input a string:\n");
	mygets(pout,cnt);

	return 0;
}
