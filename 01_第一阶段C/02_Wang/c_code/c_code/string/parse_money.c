#include <stdio.h>
#include <string.h>

int get_worker_salary(char *pstr,int *psalary,int cnt);
char *get_one_money(char *pstr,int *salary);
int get_sum(int *pi,int cnt);
int print_salary(int *pi,int cnt);

int main()
{
	char buf[] = "lisi$2000#Zhangsan$3000#wangwu$3200#zhaoda$3600";
	int arr[4] = {0};

	get_worker_salary(buf,arr,4);

	print_salary(arr,4);


	printf("The ave of salary is %.2f\n",(float)get_sum(arr,4)/4);
	return 0;
}

int get_worker_salary(char *pstr,int *psalary,int cnt)
{
	int i = 0;
	char *pret =  NULL;

	pret = get_one_money(pstr,psalary+i);
	while(pret != NULL && i < cnt)
	{
		i++;
		pret = get_one_money(pret,psalary+i);
	}

	return 0;
}

char *get_one_money(char *pstr,int *salary)
{
	char *p = NULL;

	p = strchr(pstr,'$');
	p++;

	sscanf(p,"%d",salary);

	p = strchr(p,'#');
	if(p == NULL)
	{
		return NULL;
	}
	else
	{
		p++;//跳过‘#’
		return p;
	}
}

int get_sum(int *pi,int cnt)
{
	int sum = 0;
	int *pt = NULL;

	for(pt = pi;pt < pi + cnt;pt++)
	{
		sum+=*pt;
	}

	return sum;
}

int print_salary(int *pi,int cnt)
{
	int *p = NULL;

	for(p = pi;p < pi + cnt;p++)
	{
		printf("%d ",*p);
	}
	putchar('\n');

	return 0;
}
