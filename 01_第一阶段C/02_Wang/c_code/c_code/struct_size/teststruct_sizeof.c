#include <stdio.h>
struct T
{
	int i;
	char c1;
	double d;
	char c2;
};

struct T1
{
	double d;
	int i;
	char c1;
	char c2;
};
int main(int argc,char *argv[])
{
	printf("size of struct T = %lu\n",(unsigned long)sizeof(struct T));
	printf("size of struct T1 = %lu\n",(unsigned long)sizeof(struct T1));

	return 0;
}
