#include <stdio.h>

int count_times(char buf[],char ch);

int main()
{
	char str[] = "asgdaasdfas";

	printf("The occur-times of a is %d\n",count_times(str,'a'));
	return 0;
}

int count_times(char buf[],char ch)
{
	int i = 0;
	int cnt = 0;

	if(ch == '\0')
	{
		printf("The param ch is invalid\n");
		return -1;
	}

	while(buf[i] != '\0')
	{
		if(buf[i] == ch)
		{
			cnt++;
		}

		i++;
	}

	return cnt;
}
