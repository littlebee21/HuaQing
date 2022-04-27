#include <stdio.h>

#define N 10
int main()
{
	char arr[N] = {'q','w','e','r','t','e','e','t','q','t'};
	int cnt = N;
	char ch = '\0';
	char *p = NULL;
	char *q = NULL;

	/*用户输入一个字符*/
	printf("Please input a char:\n");
	ch = getchar();

	/*删除ch*/
	for(p = arr,q=arr;p < arr + N;p++)
	{
		if(*p != ch)
		{
			*q = *p;
			q++;
		}
		else
		{
			cnt--;
		}
	}

	/*输出字符数组*/
	for(p = arr;p < arr + cnt;p++)
	{
		putchar(*p);
	}
	putchar('\n');
	return 0;
}
