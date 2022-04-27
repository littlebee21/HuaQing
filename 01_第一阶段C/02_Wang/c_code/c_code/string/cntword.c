#include <stdio.h>

int input_string(char *pstr,int cnt);
char *mygets(char *pout,int size);
int get_word_number(char *pstr);

#define STR_LEN 40
int main()
{
	char buf[STR_LEN] = "";

	input_string(buf,STR_LEN);


	printf("The number of words=%d\n",get_word_number(buf));
	return 0;
}

int input_string(char *pstr,int cnt)
{
	printf("Please input a string:\n");
	mygets(pstr,cnt);

	return 0;
}

int get_word_number(char *pstr)
{
	int cnt = 0;
	char *p = NULL;

	p = pstr;
	while(*p != '\0')
	{
		/*跳过空格*/
		while(*p == ' ')
		{
			p++;
		}

		/*检查是否到达尾部*/
		if(*p == '\0')
		{
			break;
		}

		/*修改单词第一字母*/
		cnt++;

		/*跳过本单词后面的字符直到遇到空格或'\0'*/
		while(*p != ' ' && *p != '\0')
		{
			p++;
		}
	}

	return cnt;
}
