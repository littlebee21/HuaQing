#include <stdio.h>

int my_strlen(char str[]);
int main()
{
	char buf1[] = {'a','b','c'};
	char buf2[] = {'a','b','c','\0'};
	char buf3[] = "abcde";

	//printf("strlen of buf1 = %d\n",my_strlen(buf1));//无意义，buf1不是字符串
	printf("size of buf1=%lu\n",sizeof(buf1));
	printf("strlen of buf2 = %d,size of buf2=%lu\n",my_strlen(buf2),sizeof(buf2));
	printf("strlen of buf3 = %d,size of buf3=%lu\n",my_strlen(buf3),sizeof(buf3));

	printf("%c\n","hello"[1]);

	"hello"[1] = 'E';

	printf("111111111111111\n");
	return 0;
}

int my_strlen(char str[])
{
	int cnt = 0;
	int i = 0;

	while(str[i] != '\0')
	{
		cnt++;
		i++;
	}
	return cnt;
}
