#include <stdio.h>

void f1();
void f2();
void f3();
extern int gx;
int main(int argc,char *argv[])
{

	f1();
	f2();
	gx += 2;
	f3();	
	return 0;
}
