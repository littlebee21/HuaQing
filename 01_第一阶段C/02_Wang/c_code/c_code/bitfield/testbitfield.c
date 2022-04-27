#include <stdio.h>

struct person_bf
{
	char name[20];

	unsigned short sex:2;//00 Female  01Male 10 XX  
	unsigned short age:14;
};

struct person_nbf
{
	char name[20];

	unsigned short sexandage;
};

#define GET_SEX(x) ((x.sexandage) & 0x3)
#define GET_AGE(x) ((x.sexandage) >> 2)

int main(int argc,char *argv[])
{
	struct person_bf t1 = {"zhangsan"};
	struct person_nbf t2 = {"zhangsan"};

	t1.sex = 1;
	t1.age = 39;
	printf("Name:%s,sex:%d,age:%d\n",t1.name,t1.sex,t1.age);

	t2.sexandage = (39 << 2) | 1;
	printf("Name:%s,sex:%d,age:%d\n",t2.name,GET_SEX(t2),GET_AGE(t2));

	return 0;
}
