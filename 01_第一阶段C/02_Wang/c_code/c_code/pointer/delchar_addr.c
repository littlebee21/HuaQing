#include <stdio.h>

#define N 10
int main()
{
	char arr[N] = {'q','w','e','r','t','e','e','t','q','t'};
	int cnt = N;
	char ch = '\0';
	int i = 0;
	int j = 0;

	/*用户输入一个字符*/
	printf("Please input a char:\n");
	ch = getchar();

	/*删除ch*/
	for(i = 0;i < N;i++)
	{
		if(*(arr+i) != ch)
		{
			*(arr+j) = *(arr+i);
			j++;
		}
		else
		{
			cnt--;
		}
	}

	/*输出字符数组*/
	for(i = 0;i < cnt;i++)
	{
		putchar(*(arr+i));
	}
	putchar('\n');
	return 0;
}
