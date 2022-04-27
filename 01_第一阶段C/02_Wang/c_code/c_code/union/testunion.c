#include <stdio.h>

union my_un
{
	unsigned short us;
	unsigned int  ui;
};


int main(int argc,char *argv[])
{
	union my_un u1 ={0x1234};

	printf("u1.us=%x\n",u1.us);
	printf("u1.ui=%x\n",u1.ui);

	u1.ui = 0x12345678;
	printf("u1.us=%x\n",u1.us);
	printf("u1.ui=%x\n",u1.ui);
	return 0;
}
