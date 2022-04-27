#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct my_complex
{
	double r;
	double v;
};

struct my_complex add_complex(struct my_complex st1,struct my_complex st2);
struct my_complex add_complex2(struct my_complex *pst1,struct my_complex *pst2);
int add_complex3(struct my_complex *pst1,struct my_complex *pst2,struct my_complex *pout);
struct my_complex * add_complex4(struct my_complex *pst1,struct my_complex *pst2);
int main(int argc,char *argv[])
{
	struct my_complex t1 = {0.0};
	struct my_complex t2 = {0.0};

	printf("Please input real-value and virtual-value:\n");
	scanf("%lf%lf",&t1.r,&t1.v);
	
	printf("Please input real-value and virtual-value:\n");
	scanf("%lf%lf",&t2.r,&t2.v);

	/*
	传参和函数返回的效率均低
	{
		struct my_complex t3 = {0.0};
		t3 = add_complex1(t1,t2);
		printf("After add,r-value=%.2f,v-value=%.2f\n",t3.r,t3.v);
	}*/

	/*
	函数返回的效率低
	{
		struct my_complex t3 = {0.0};
		t3 = add_complex2(&t1,&t2);
		printf("After add,r-value=%.2f,v-value=%.2f\n",t3.r,t3.v);
	}*/

	
	{
		struct my_complex t3 = {0.0};
		add_complex3(&t1,&t2,&t3);
		printf("After add,r-value=%.2f,v-value=%.2f\n",t3.r,t3.v);
	}
	

	/*{
		struct my_complex *pret = NULL;
		pret = add_complex4(&t1,&t2);
		printf("After add,r-value=%.2f,v-value=%.2f\n",pret->r,pret->v);

		free(pret);//一旦不再使用pret指向空间，必须要对其进行free，否则会造成内存泄漏
		pret = NULL;
	}*/


	return 0;
}

struct my_complex add_complex1(struct my_complex st1,struct my_complex st2)
{
	struct my_complex st3 = {0.0};

	st3.r = st1.r + st2.r;
	st3.v = st1.v + st2.v;

	return st3;
}

struct my_complex add_complex2(struct my_complex *pst1,struct my_complex *pst2)
{
	struct my_complex st3 = {0.0};

	st3.r = pst1->r + pst2->r;
	st3.v = pst1->v + pst2->v;

	return st3;
}

int add_complex3(struct my_complex *pst1,struct my_complex *pst2,struct my_complex *pout)
{
	pout->r = pst1->r + pst2->r;
	pout->v = pst1->v + pst2->v;

	return 0;
}

struct my_complex * add_complex4(struct my_complex *pst1,struct my_complex *pst2)
{
	struct my_complex *pout = NULL;

	pout = (struct my_complex *)malloc(sizeof(struct my_complex));
	if(NULL == pout)
	{
		printf("Malloc Failed\n");
		return NULL;
	}
	memset(pout,0,sizeof(struct my_complex));

	pout->r = pst1->r + pst2->r;
	pout->v = pst1->v + pst2->v;

	return pout;	
}
