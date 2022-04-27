#include <stdio.h>

int main(int argc,char *argv[])
{
	double arr[1024*1024] ={0};//栈溢出

	arr[0] = 1.0;

	printf("arr[0]=%f\n",arr[0]);
	return 0;
}
