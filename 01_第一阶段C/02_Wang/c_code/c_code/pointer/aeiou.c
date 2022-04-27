#include <stdio.h>

int count_aeiou(char *pstr,int *pret,int cnt);
int print_int_arr(int *pi,int cnt);
int main(int argc,char *argv[])
{
	int retarr[5] = {0};

	if(argc < 2)
	{
		printf("The argument is too few,Usage:./aeiou  sadjgfhasgh\n");
		return 1;
	}

	count_aeiou(argv[1],retarr,5);

	print_int_arr(retarr,5);

	return 0;
}

int print_int_arr(int *pi,int cnt)
{
	int *p = pi;

	for(;p < pi + cnt;p++)
	{
		printf("%d ",*p);
	}
	putchar('\n');

	return 0;
}

int count_aeiou(char *pstr,int *pret,int cnt)
{
	char *p = pstr;
	int *pi = NULL;;

	if(cnt < 5)
	{
		printf("Input param is invalid\n");
		return -1;
	}

	/*
	for(pi = pret;pi < pret + cnt;pi++)
	{
		*pi = 0;
	}
	*/
	memset(pret,0x00,cnt * sizeof(int));

	while(*p != '\0')
	{
		switch(*p)
		{
			case 'a':
			case 'A':
				(*pret)++;
				break;
			case 'e':
			case 'E':
				(*(pret+1))++;
				break;
			case 'i':
			case 'I':
				(*(pret+2))++;
				break;
			case 'o':
			case 'O':
				(*(pret+3))++;
				break;
			case 'u':
			case 'U':
				(*(pret+4))++;
				break;
			default:
				break;
		}
		p++;
	}

	return 0;
}
