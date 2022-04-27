#include <stdio.h>

int count_pieces(int m,int *pret,int cnt);
int print_int_arr(int *pi,int cnt);
int main(int argc,char *argv[])
{
	int money = 0;
	int rmb[7] = {0};

	if(argc < 2)
	{
		printf("The argument is too few,Usage:./money 10000\n");
		return 1;
	}

	sscanf(argv[1],"%d",&money);

	count_pieces(money,rmb,7);
	print_int_arr(rmb,7);

	return 0;
}

int print_int_arr(int *pi,int cnt)
{
	int *p = pi;

	printf("%6d%6d%6d%6d%6d%6d%6d\n",100,50,20,10,5,2,1);
	for(;p < pi + cnt;p++)
	{
		printf("%6d",*p);
	}
	putchar('\n');

	return 0;
}

int count_pieces(int m,int *pret,int cnt)
{
	int rmb_arr[7] = {100,50,20,10,5,2,1};
	int *p = NULL;

	if(cnt < 7)
	{
		printf("Input param is invalid\n");
		return -1;
	}
	
	for(p = rmb_arr;p < rmb_arr+7;p++)
	{
		*(pret + (p - rmb_arr))=m / *p;
		m = m % *p;
	}

	return 0;
}
