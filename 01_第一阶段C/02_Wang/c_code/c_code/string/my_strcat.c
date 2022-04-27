#include <stdio.h>

int my_strcat(char inbuf1[],char inbuf2[],char outbuf[]);
int main()
{
	//char str1[] = "abcd";
	char str1[] = {'a','b','c','d'};
	char str2[] = "-1234";
	char str3[sizeof(str1) + sizeof(str2)] = "";

	my_strcat(str1,str2,str3);

	printf("The str3 is %s\n",str3);
	return 0;
}

int my_strcat(char inbuf1[],char inbuf2[],char outbuf[])
{
	int i = 0;
	int j = 0;

	while(inbuf1[i] != '\0')
	{
		outbuf[i] = inbuf1[i];
		i++;
	}

	while(inbuf2[j] != '\0')
	{
		outbuf[i] = inbuf2[j];
		i++;
		j++;
	}
	outbuf[i] = inbuf2[j];//copy '\0'
	
	return i+1;
}

