#include <stdio.h>

int is_little_endian_v1();
int is_little_endian_v2();

int main(int argc,char *argv[])
{
	if(is_little_endian_v2())
	{
		printf("This PC is little-endian\n");
	}
	else
	{
		printf("This PC is big-endian\n");
	}

	return 0;
}

int is_little_endian_v1()
{
	unsigned int x = 0xaabbccdd;
	unsigned char *p = (unsigned char *)&x;

	if(*p == 0xdd)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int is_little_endian_v2()
{
	union Temp
	{
		unsigned int v1;
		unsigned char v2;
	};

	union Temp u = {0xaabbccdd};

	if(u.v2 == 0xdd)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

short my_htons(short v)
{
	if(is_little_endian_v2())
	{//host is little-endian
		signed char *p = (signed char *)&v;
		signed char t;
		
		t = *p;
		*p = *(p+1);
		*(p+1) = t;

		return v;
	}
	else
	{//host is big-endian
		return v;
	}
}
