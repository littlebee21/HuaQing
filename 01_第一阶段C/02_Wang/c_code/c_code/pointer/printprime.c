#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_prime(int x);
int print_prime(int *pout,int cnt);
int get_prime1(int vm,int *pout,int vk);
int * get_prime2(int vm,int vk);
int main(int argc,char *argv[])
{
	int m = 0;
	int k = 0;
	int *pret = NULL;

	if(argc < 3)
	{
		printf("The argument is too few,Usage:./prime 19  20\n");
		return 1;
	}

	sscanf(argv[1],"%d",&m);
	sscanf(argv[2],"%d",&k);

	/*
	pret = (int *)malloc(k * sizeof(int));
	if(NULL == pret)
	{
		printf("Malloc failed\n");
		return 2;
	}

	get_prime1(m,pret,k);
	*/

	pret = get_prime2(m,k);

	print_prime(pret,k);
	
	free(pret);
	pret = NULL;

	return 0;
}

int is_prime(int x);
int get_prime1(int vm,int *pout,int vk)
{
	int i = 0;

	vm++;

	while(i < vk)
	{
		if(is_prime(vm))
		{
			*(pout + i) = vm;
			i++;
		}
		vm++;
	}
	
	return 0;
}

int * get_prime2(int vm,int vk)
{
	int i = 0;
	int *pout = NULL;

	pout = (int *)malloc(vk * sizeof(int));
	if(NULL == pout)
	{
		printf("Malloc failed\n");
		return NULL;
	}
	memset(pout,0,vk*sizeof(int));

	vm++;

	while(i < vk)
	{
		if(is_prime(vm))
		{
			*(pout + i) = vm;
			i++;
		}
		vm++;
	}
	
	return pout;
}

int print_prime(int *pout,int cnt)
{
	int *p = pout;

	for(;p < pout + cnt;p++)
	{
		printf("%d ",*p);
	}
	putchar('\n');

	return 0;
}

int is_prime(int x)
{
	int i = 0;

	for(i = 2;i < x;i++)
	{
		if(x % i == 0)
		{
			break;
		}
	}

	if(i == x)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
