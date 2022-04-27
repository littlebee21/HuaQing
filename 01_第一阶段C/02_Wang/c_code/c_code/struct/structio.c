#include <stdio.h>

#define NAME_LEN 20
struct date
{
	int y;
	int m;
	int d;
};

struct stu
{
	char name[NAME_LEN];
	char sex;
	float score;
	struct date birth;
};

char *mygets(char *pout,int size);
int main(int argc,char *argv[])
{
	struct stu st = {""};

	printf("Please input your name:\n");
	mygets(st.name,NAME_LEN);

	printf("Please input your sex:\n");
	st.sex = getchar();
	
	printf("Please input your score:\n");
	scanf("%f",&st.score);

	printf("Please input your birthday:2000 10 9\n");
	scanf("%d%d%d",&st.birth.y,&st.birth.m,&st.birth.d);


	printf("Your information:\n");
	printf("Name:%s Sex:%c Score:%.1f Birth:%d-%d-%d\n",
			st.name,
			st.sex,
			st.score,
			st.birth.y,
			st.birth.m,
			st.birth.d
	      );

	return 0;
}
