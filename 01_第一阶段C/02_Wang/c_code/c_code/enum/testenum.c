#include <stdio.h>
/*
 * enum更加适用于给连续多个整型常量命名
enum week
{
	SUN,
	MON,
	TUE,
	WED,
	THU,
	FRI,
	SAT
};

//不建议使用宏定义
#define SUN 0
#define	MON 1
#define	TUE 2
#define	WED 3
#define	THU 4
#define	FRI 5
#define	SAT 6

*/



enum XYZ
{
	N1 = 2,
	N2,
	N3 = 10,
	N4,
};

#define X2 6

int main(int argc,char *argv[])
{
	int x = N4; 
	enum XYZ y = 100;
	int z = X2;

	printf("x=%d\n",x);

	x = N2;
	printf("x=%d\n",x);
	
	printf("y=%d\n",y);
	
	printf("z=%d\n",z);

	printf("sizeof enum XYZ = %lu\n",sizeof(enum XYZ));
	return 0;
}
