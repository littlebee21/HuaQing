#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int input_number();
int select_sort(int *pint,int num);
int print_sort(int *pint,int num);
int main(int argc,char *argv[])
{
	int cnt = input_number();
	int *pi = NULL;
	int i = 0;

	if(cnt <= 0)
	{
		printf("Your input is invalid\n");
		return 1;
	}

	pi = (int *)malloc(cnt * sizeof(int));
	if(NULL == pi)
	{
		printf("Malloc failed\n");
		return 2;
	}
	
	srand(time(NULL));

	for(i = 0;i < cnt;i++)
	{
		*(pi + i) = rand() % 1000;
	}
        

	select_sort(pi,cnt);
	print_sort(pi,cnt);
	
	free(pi);
	pi = NULL;

	//........
	return 0;
}
int print_sort(int *pint,int num)
{
	int *p = NULL;

	for(p = pint;p < pint + num;p++)
	{
		printf("%d ",*p);
	}
	putchar('\n');

	return 0;
}

int select_sort(int *pint,int num)
{
	int i = 0;
	int j = 0;
	int min = 0;
	int t = 0;

	for(i = 0;i < num;i++)
	{
		min = i;
		for(j = i + 1;j < num;j++)
		{
			if(*(pint + j) < *(pint + min))
			{
				min = j;
			}
		}

		if(min != i)
		{
			t = *(pint + i);
			*(pint + i) = *(pint + min);
			*(pint + min) = t;
		}
	}

	return 0;
}

int input_number()
{
	int n = 0;

	printf("Please input a number:\n");
	scanf("%d",&n);

	while(getchar() != '\n')
	{
	}

	return n;
}
