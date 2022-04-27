#include <stdio.h>

void f0()
{
	printf("Call 0\n");
}
void f1()
{
	printf("Call 1\n");
}
void f2()
{
	printf("Call 2\n");
}
void f3()
{
	printf("Call 3\n");
}
void f4()
{
	printf("Call 4\n");
}
void f5()
{
	printf("Call 5\n");
}
void f6()
{
	printf("Call 6\n");
}
void f7()
{
	printf("Call 7\n");
}
void f8()
{
	printf("Call 8\n");
}
void f9()
{
	printf("Call 9\n");
}

typedef void (*PF)();

char *mygets(char *pout,int size);
int input_numstr(char *pstr,int cnt);
int parse_numstr(char *pstr);

int main(int argc,char *argv[])
{
	char buf[20] = "";

	input_numstr(buf,20);

	parse_numstr(buf);
	return 0;
}

int parse_numstr(char *pstr)
{
	PF arr[10] = {f0,f1,f2,f3,f4,f5,f6,f7,f8,f9};
	char *p = pstr;
	
	while(*p != '\0')
	{
		if(*p >= '0' && *p <= '9')
		{
			arr[*p -'0']();
		}
		p++;
	}

	return 0;
}

int input_numstr(char *pstr,int cnt)
{
	printf("Please input a numric-string:\n");
	mygets(pstr,cnt);

	return 0;
}
