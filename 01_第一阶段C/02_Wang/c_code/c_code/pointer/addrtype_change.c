#include <stdio.h>

int main()
{
	/*
	unsigned int x = 0x12345678;
	unsigned short *pus = (unsigned short *)&x;

	printf("*pus = 0x%x\n",*pus);
	printf("*(pus+1) = 0x%x\n",*(pus+1));
	
	printf("x = 0x%x\n",x);
	*/

	unsigned short s = 0x1234;
	unsigned int *pui = (unsigned int *)&s;

	printf("*pui=0x%x\n",*pui);//越界两个字节
	return 0;
}
