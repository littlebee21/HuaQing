#include <stdio.h>

#define NAME_LEN  20
#define N  5
struct stu
{
	char name[NAME_LEN];
	int age;
};

int find_oldest_stu(struct stu *pstu,int cnt);
int main(int argc,char *argv[])
{
	struct stu arr[N] = {
				{"Ruhua",24},
				{"Siyu",26},
				{"Cengyu",22},
				{"Luoyan",23},
				{"Biyue",25},
			    };

	int ret = 0;

	ret = find_oldest_stu(arr,N);

	printf("The oldest stu name:%s,age:%d\n",(arr+ret)->name,(arr+ret)->age);
	return 0;
}

int find_oldest_stu(struct stu *pstu,int cnt)
{
	int old = 0;
	struct stu *pt = NULL;

	for(pt = pstu + 1;pt < pstu + cnt;pt++)
	{
		if(pt->age > (pstu+old)->age)
		{
			old = pt - pstu;
		}
	}

	return old;
}
