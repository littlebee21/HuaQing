#include "mysort.h"

#define N1 5
#define N2 6

struct T
{
	int a;
	float b;
};

int intcmp(void *pv1,void *pv2);
int dblcmp(void *pv1,void *pv2);
int mystrcmp(void *pv1,void *pv2);
int stcmp(void *pv1,void *pv2);
int main(int argc,char *argv[])
{
	int intarr[N1] = {99,76,83,56,62};
	double dblarr[N1] = {99.9,76.6,83.3,56.6,62.2};
	char * strarr[N2] = {"Ruhua","Siyu","Cengyu","Luoyan","Biyue","Xiuhua"};
	struct T starr[N2] = {
				{1,55.5},
				{2,66.6},
				{3,33.3},
				{4,22.2},
				{5,88.8},
				{6,11.1},
			     };

	//bubble_sort(intarr,N1,sizeof(int),intcmp);
	//select_sort(intarr,N1,sizeof(int),intcmp);
	insert_sort(intarr,N1,sizeof(int),intcmp);
	printf("After sort intarr:\n");
	{
		int i = 0;
		for(i = 0;i < N1;i++)
		{
			printf("%d ",intarr[i]);
		}
		printf("\n");
	}
	
	//bubble_sort(dblarr,N1,sizeof(double),dblcmp);
	//select_sort(dblarr,N1,sizeof(double),dblcmp);
	insert_sort(dblarr,N1,sizeof(double),dblcmp);
	printf("After sort dblarr:\n");
	{
		int i = 0;
		for(i = 0;i < N1;i++)
		{
			printf("%.1f ",dblarr[i]);
		}
		printf("\n");
	}
	
	//bubble_sort(strarr,N2,sizeof(char *),mystrcmp);
	//select_sort(strarr,N2,sizeof(char *),mystrcmp);
	insert_sort(strarr,N2,sizeof(char *),mystrcmp);
	printf("After sort strarr:\n");
	{
		int i = 0;
		for(i = 0;i < N2;i++)
		{
			printf("%s\n",strarr[i]);
		}
	}
	
	//bubble_sort(starr,N2,sizeof(struct T),stcmp);
	//select_sort(starr,N2,sizeof(struct T),stcmp);
	insert_sort(starr,N2,sizeof(struct T),stcmp);
	printf("After sort starr:\n");
	{
		int i = 0;
		for(i = 0;i < N2;i++)
		{
			printf("a=%d,b=%.1f\n",starr[i].a,starr[i].b);
		}
	}
	return 0;
}

int stcmp(void *pv1,void *pv2)
{
	if(((struct T *)pv1)->b > ((struct T *)pv2)->b)
	{
		return -1;
	}
	else if(((struct T *)pv1)->b < ((struct T *)pv2)->b)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

int intcmp(void *pv1,void *pv2)
{
	return *(int *)pv1 - *(int *)pv2;
}

int dblcmp(void *pv1,void *pv2)
{
	if(*(double *)pv1 == *(double *)pv2)
	{
		return 0;
	}
	else if(*(double *)pv1 > *(double *)pv2)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

int mystrcmp(void *pv1,void *pv2)
{
	return strcmp(*(char **)pv1,*(char **)pv2);
}
